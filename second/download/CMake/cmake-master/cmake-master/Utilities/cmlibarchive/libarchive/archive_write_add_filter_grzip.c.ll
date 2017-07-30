; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_add_filter_grzip.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.archive = type { i32, i32, %struct.archive_vtable*, i32, i8*, i32, i8*, i32, i32, i8*, %struct.archive_string, i8*, i32, i32, %struct.archive_string_conv*, i8*, i64, i64, i64, i8, i64 }
%struct.archive_vtable = type { {}*, {}*, i32 (%struct.archive*, %struct.archive_entry*)*, {}*, i64 (%struct.archive*, i8*, i64)*, i64 (%struct.archive*, i8*, i64, i64)*, i32 (%struct.archive*, %struct.archive_entry**)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*, i8**, i64*, i64*)*, {}*, i64 (%struct.archive*, i32)*, i32 (%struct.archive*, i32)*, i8* (%struct.archive*, i32)* }
%struct.archive_entry = type opaque
%struct.archive_string = type { i8*, i64, i64 }
%struct.archive_string_conv = type opaque
%struct.archive_write_filter = type { i64, %struct.archive*, %struct.archive_write_filter*, i32 (%struct.archive_write_filter*, i8*, i8*)*, i32 (%struct.archive_write_filter*)*, i32 (%struct.archive_write_filter*, i8*, i64)*, i32 (%struct.archive_write_filter*)*, i32 (%struct.archive_write_filter*)*, i8*, i8*, i32, i32, i32 }
%struct.write_grzip = type { %struct.archive_write_program_data* }
%struct.archive_write_program_data = type opaque

@.str = private unnamed_addr constant [31 x i8] c"archive_write_add_filter_grzip\00", align 1
@.str.1 = private unnamed_addr constant [22 x i8] c"Can't allocate memory\00", align 1
@.str.2 = private unnamed_addr constant [6 x i8] c"grzip\00", align 1
@.str.3 = private unnamed_addr constant [51 x i8] c"Using external grzip program for grzip compression\00", align 1

; Function Attrs: nounwind uwtable
define i32 @archive_write_add_filter_grzip(%struct.archive* %_a) #0 !dbg !13 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %f = alloca %struct.archive_write_filter*, align 8
  %data = alloca %struct.write_grzip*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !148, metadata !149), !dbg !150
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f, metadata !151, metadata !149), !dbg !152
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !153
  %call = call %struct.archive_write_filter* @__archive_write_allocate_filter(%struct.archive* %0), !dbg !154
  store %struct.archive_write_filter* %call, %struct.archive_write_filter** %f, align 8, !dbg !152
  call void @llvm.dbg.declare(metadata %struct.write_grzip** %data, metadata !155, metadata !149), !dbg !156
  br label %do.body, !dbg !157

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !158, metadata !149), !dbg !160
  %1 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !161
  %call1 = call i32 @__archive_check_magic(%struct.archive* %1, i32 -1329217314, i32 1, i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str, i32 0, i32 0)), !dbg !161
  store i32 %call1, i32* %magic_test, align 4, !dbg !161
  %2 = load i32, i32* %magic_test, align 4, !dbg !161
  %cmp = icmp eq i32 %2, -30, !dbg !161
  br i1 %cmp, label %if.then, label %if.end, !dbg !161

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !163
  br label %return, !dbg !163

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !166

do.end:                                           ; preds = %if.end
  %call2 = call noalias i8* @calloc(i64 1, i64 8) #4, !dbg !168
  %3 = bitcast i8* %call2 to %struct.write_grzip*, !dbg !168
  store %struct.write_grzip* %3, %struct.write_grzip** %data, align 8, !dbg !169
  %4 = load %struct.write_grzip*, %struct.write_grzip** %data, align 8, !dbg !170
  %cmp3 = icmp eq %struct.write_grzip* %4, null, !dbg !172
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !173

if.then4:                                         ; preds = %do.end
  %5 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !174
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %5, i32 12, i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.1, i32 0, i32 0)), !dbg !176
  store i32 -30, i32* %retval, align 4, !dbg !177
  br label %return, !dbg !177

if.end5:                                          ; preds = %do.end
  %call6 = call %struct.archive_write_program_data* @__archive_write_program_allocate(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.2, i32 0, i32 0)), !dbg !178
  %6 = load %struct.write_grzip*, %struct.write_grzip** %data, align 8, !dbg !179
  %pdata = getelementptr inbounds %struct.write_grzip, %struct.write_grzip* %6, i32 0, i32 0, !dbg !180
  store %struct.archive_write_program_data* %call6, %struct.archive_write_program_data** %pdata, align 8, !dbg !181
  %7 = load %struct.write_grzip*, %struct.write_grzip** %data, align 8, !dbg !182
  %pdata7 = getelementptr inbounds %struct.write_grzip, %struct.write_grzip* %7, i32 0, i32 0, !dbg !184
  %8 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %pdata7, align 8, !dbg !184
  %cmp8 = icmp eq %struct.archive_write_program_data* %8, null, !dbg !185
  br i1 %cmp8, label %if.then9, label %if.end10, !dbg !186

if.then9:                                         ; preds = %if.end5
  %9 = load %struct.write_grzip*, %struct.write_grzip** %data, align 8, !dbg !187
  %10 = bitcast %struct.write_grzip* %9 to i8*, !dbg !187
  call void @free(i8* %10) #4, !dbg !189
  %11 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !190
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %11, i32 12, i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.1, i32 0, i32 0)), !dbg !191
  store i32 -30, i32* %retval, align 4, !dbg !192
  br label %return, !dbg !192

if.end10:                                         ; preds = %if.end5
  %12 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !193
  %name = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %12, i32 0, i32 9, !dbg !194
  store i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.2, i32 0, i32 0), i8** %name, align 8, !dbg !195
  %13 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !196
  %code = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %13, i32 0, i32 10, !dbg !197
  store i32 12, i32* %code, align 8, !dbg !198
  %14 = load %struct.write_grzip*, %struct.write_grzip** %data, align 8, !dbg !199
  %15 = bitcast %struct.write_grzip* %14 to i8*, !dbg !199
  %16 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !200
  %data11 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %16, i32 0, i32 8, !dbg !201
  store i8* %15, i8** %data11, align 8, !dbg !202
  %17 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !203
  %open = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %17, i32 0, i32 4, !dbg !204
  store i32 (%struct.archive_write_filter*)* @archive_write_grzip_open, i32 (%struct.archive_write_filter*)** %open, align 8, !dbg !205
  %18 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !206
  %options = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %18, i32 0, i32 3, !dbg !207
  store i32 (%struct.archive_write_filter*, i8*, i8*)* @archive_write_grzip_options, i32 (%struct.archive_write_filter*, i8*, i8*)** %options, align 8, !dbg !208
  %19 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !209
  %write = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %19, i32 0, i32 5, !dbg !210
  store i32 (%struct.archive_write_filter*, i8*, i64)* @archive_write_grzip_write, i32 (%struct.archive_write_filter*, i8*, i64)** %write, align 8, !dbg !211
  %20 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !212
  %close = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %20, i32 0, i32 6, !dbg !213
  store i32 (%struct.archive_write_filter*)* @archive_write_grzip_close, i32 (%struct.archive_write_filter*)** %close, align 8, !dbg !214
  %21 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !215
  %free = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %21, i32 0, i32 7, !dbg !216
  store i32 (%struct.archive_write_filter*)* @archive_write_grzip_free, i32 (%struct.archive_write_filter*)** %free, align 8, !dbg !217
  %22 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !218
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %22, i32 -1, i8* getelementptr inbounds ([51 x i8], [51 x i8]* @.str.3, i32 0, i32 0)), !dbg !219
  store i32 -20, i32* %retval, align 4, !dbg !220
  br label %return, !dbg !220

return:                                           ; preds = %if.end10, %if.then9, %if.then4, %if.then
  %23 = load i32, i32* %retval, align 4, !dbg !221
  ret i32 %23, !dbg !221
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare %struct.archive_write_filter* @__archive_write_allocate_filter(%struct.archive*) #2

declare i32 @__archive_check_magic(%struct.archive*, i32, i32, i8*) #2

; Function Attrs: nounwind
declare noalias i8* @calloc(i64, i64) #3

declare void @archive_set_error(%struct.archive*, i32, i8*, ...) #2

declare %struct.archive_write_program_data* @__archive_write_program_allocate(i8*) #2

; Function Attrs: nounwind
declare void @free(i8*) #3

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_grzip_open(%struct.archive_write_filter* %f) #0 !dbg !141 {
entry:
  %f.addr = alloca %struct.archive_write_filter*, align 8
  %data = alloca %struct.write_grzip*, align 8
  store %struct.archive_write_filter* %f, %struct.archive_write_filter** %f.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f.addr, metadata !222, metadata !149), !dbg !223
  call void @llvm.dbg.declare(metadata %struct.write_grzip** %data, metadata !224, metadata !149), !dbg !225
  %0 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !226
  %data1 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %0, i32 0, i32 8, !dbg !227
  %1 = load i8*, i8** %data1, align 8, !dbg !227
  %2 = bitcast i8* %1 to %struct.write_grzip*, !dbg !228
  store %struct.write_grzip* %2, %struct.write_grzip** %data, align 8, !dbg !225
  %3 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !229
  %4 = load %struct.write_grzip*, %struct.write_grzip** %data, align 8, !dbg !230
  %pdata = getelementptr inbounds %struct.write_grzip, %struct.write_grzip* %4, i32 0, i32 0, !dbg !231
  %5 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %pdata, align 8, !dbg !231
  %call = call i32 @__archive_write_program_open(%struct.archive_write_filter* %3, %struct.archive_write_program_data* %5, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.2, i32 0, i32 0)), !dbg !232
  ret i32 %call, !dbg !233
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_grzip_options(%struct.archive_write_filter* %f, i8* %key, i8* %value) #0 !dbg !115 {
entry:
  %f.addr = alloca %struct.archive_write_filter*, align 8
  %key.addr = alloca i8*, align 8
  %value.addr = alloca i8*, align 8
  store %struct.archive_write_filter* %f, %struct.archive_write_filter** %f.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f.addr, metadata !234, metadata !149), !dbg !235
  store i8* %key, i8** %key.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %key.addr, metadata !236, metadata !149), !dbg !237
  store i8* %value, i8** %value.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %value.addr, metadata !238, metadata !149), !dbg !239
  %0 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !240
  %1 = load i8*, i8** %key.addr, align 8, !dbg !241
  %2 = load i8*, i8** %value.addr, align 8, !dbg !242
  ret i32 -20, !dbg !243
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_grzip_write(%struct.archive_write_filter* %f, i8* %buff, i64 %length) #0 !dbg !142 {
entry:
  %f.addr = alloca %struct.archive_write_filter*, align 8
  %buff.addr = alloca i8*, align 8
  %length.addr = alloca i64, align 8
  %data = alloca %struct.write_grzip*, align 8
  store %struct.archive_write_filter* %f, %struct.archive_write_filter** %f.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f.addr, metadata !244, metadata !149), !dbg !245
  store i8* %buff, i8** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buff.addr, metadata !246, metadata !149), !dbg !247
  store i64 %length, i64* %length.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %length.addr, metadata !248, metadata !149), !dbg !249
  call void @llvm.dbg.declare(metadata %struct.write_grzip** %data, metadata !250, metadata !149), !dbg !251
  %0 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !252
  %data1 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %0, i32 0, i32 8, !dbg !253
  %1 = load i8*, i8** %data1, align 8, !dbg !253
  %2 = bitcast i8* %1 to %struct.write_grzip*, !dbg !254
  store %struct.write_grzip* %2, %struct.write_grzip** %data, align 8, !dbg !251
  %3 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !255
  %4 = load %struct.write_grzip*, %struct.write_grzip** %data, align 8, !dbg !256
  %pdata = getelementptr inbounds %struct.write_grzip, %struct.write_grzip* %4, i32 0, i32 0, !dbg !257
  %5 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %pdata, align 8, !dbg !257
  %6 = load i8*, i8** %buff.addr, align 8, !dbg !258
  %7 = load i64, i64* %length.addr, align 8, !dbg !259
  %call = call i32 @__archive_write_program_write(%struct.archive_write_filter* %3, %struct.archive_write_program_data* %5, i8* %6, i64 %7), !dbg !260
  ret i32 %call, !dbg !261
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_grzip_close(%struct.archive_write_filter* %f) #0 !dbg !143 {
entry:
  %f.addr = alloca %struct.archive_write_filter*, align 8
  %data = alloca %struct.write_grzip*, align 8
  store %struct.archive_write_filter* %f, %struct.archive_write_filter** %f.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f.addr, metadata !262, metadata !149), !dbg !263
  call void @llvm.dbg.declare(metadata %struct.write_grzip** %data, metadata !264, metadata !149), !dbg !265
  %0 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !266
  %data1 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %0, i32 0, i32 8, !dbg !267
  %1 = load i8*, i8** %data1, align 8, !dbg !267
  %2 = bitcast i8* %1 to %struct.write_grzip*, !dbg !268
  store %struct.write_grzip* %2, %struct.write_grzip** %data, align 8, !dbg !265
  %3 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !269
  %4 = load %struct.write_grzip*, %struct.write_grzip** %data, align 8, !dbg !270
  %pdata = getelementptr inbounds %struct.write_grzip, %struct.write_grzip* %4, i32 0, i32 0, !dbg !271
  %5 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %pdata, align 8, !dbg !271
  %call = call i32 @__archive_write_program_close(%struct.archive_write_filter* %3, %struct.archive_write_program_data* %5), !dbg !272
  ret i32 %call, !dbg !273
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_grzip_free(%struct.archive_write_filter* %f) #0 !dbg !144 {
entry:
  %f.addr = alloca %struct.archive_write_filter*, align 8
  %data = alloca %struct.write_grzip*, align 8
  store %struct.archive_write_filter* %f, %struct.archive_write_filter** %f.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f.addr, metadata !274, metadata !149), !dbg !275
  call void @llvm.dbg.declare(metadata %struct.write_grzip** %data, metadata !276, metadata !149), !dbg !277
  %0 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !278
  %data1 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %0, i32 0, i32 8, !dbg !279
  %1 = load i8*, i8** %data1, align 8, !dbg !279
  %2 = bitcast i8* %1 to %struct.write_grzip*, !dbg !280
  store %struct.write_grzip* %2, %struct.write_grzip** %data, align 8, !dbg !277
  %3 = load %struct.write_grzip*, %struct.write_grzip** %data, align 8, !dbg !281
  %pdata = getelementptr inbounds %struct.write_grzip, %struct.write_grzip* %3, i32 0, i32 0, !dbg !282
  %4 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %pdata, align 8, !dbg !282
  %call = call i32 @__archive_write_program_free(%struct.archive_write_program_data* %4), !dbg !283
  %5 = load %struct.write_grzip*, %struct.write_grzip** %data, align 8, !dbg !284
  %6 = bitcast %struct.write_grzip* %5 to i8*, !dbg !284
  call void @free(i8* %6) #4, !dbg !285
  ret i32 0, !dbg !286
}

declare i32 @__archive_write_program_open(%struct.archive_write_filter*, %struct.archive_write_program_data*, i8*) #2

declare i32 @__archive_write_program_write(%struct.archive_write_filter*, %struct.archive_write_program_data*, i8*, i64) #2

declare i32 @__archive_write_program_close(%struct.archive_write_filter*, %struct.archive_write_program_data*) #2

declare i32 @__archive_write_program_free(%struct.archive_write_program_data*) #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!145, !146}
!llvm.ident = !{!147}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !12)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_add_filter_grzip.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4, !5}
!4 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!5 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !6, size: 64, align: 64)
!6 = !DICompositeType(tag: DW_TAG_structure_type, name: "write_grzip", file: !1, line: 40, size: 64, align: 64, elements: !7)
!7 = !{!8}
!8 = !DIDerivedType(tag: DW_TAG_member, name: "pdata", scope: !6, file: !1, line: 41, baseType: !9, size: 64, align: 64)
!9 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !10, size: 64, align: 64)
!10 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_write_program_data", file: !11, line: 146, flags: DIFlagFwdDecl)
!11 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!12 = !{!13, !115, !141, !142, !143, !144}
!13 = distinct !DISubprogram(name: "archive_write_add_filter_grzip", scope: !1, file: !1, line: 53, type: !14, isLocal: false, isDefinition: true, scopeLine: 54, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!14 = !DISubroutineType(types: !15)
!15 = !{!16, !17}
!16 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!17 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !18, size: 64, align: 64)
!18 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive", file: !19, line: 89, size: 1280, align: 64, elements: !20)
!19 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!20 = !{!21, !23, !24, !88, !89, !90, !91, !92, !93, !94, !95, !103, !104, !105, !106, !109, !110, !111, !112, !113, !114}
!21 = !DIDerivedType(tag: DW_TAG_member, name: "magic", scope: !18, file: !19, line: 96, baseType: !22, size: 32, align: 32)
!22 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!23 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !18, file: !19, line: 97, baseType: !22, size: 32, align: 32, offset: 32)
!24 = !DIDerivedType(tag: DW_TAG_member, name: "vtable", scope: !18, file: !19, line: 103, baseType: !25, size: 64, align: 64, offset: 64)
!25 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !26, size: 64, align: 64)
!26 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_vtable", file: !19, line: 63, size: 832, align: 64, elements: !27)
!27 = !{!28, !30, !31, !38, !39, !53, !59, !64, !65, !72, !73, !77, !81}
!28 = !DIDerivedType(tag: DW_TAG_member, name: "archive_close", scope: !26, file: !19, line: 64, baseType: !29, size: 64, align: 64)
!29 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !14, size: 64, align: 64)
!30 = !DIDerivedType(tag: DW_TAG_member, name: "archive_free", scope: !26, file: !19, line: 65, baseType: !29, size: 64, align: 64, offset: 64)
!31 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_header", scope: !26, file: !19, line: 66, baseType: !32, size: 64, align: 64, offset: 128)
!32 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !33, size: 64, align: 64)
!33 = !DISubroutineType(types: !34)
!34 = !{!16, !17, !35}
!35 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !36, size: 64, align: 64)
!36 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_entry", file: !37, line: 180, flags: DIFlagFwdDecl)
!37 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!38 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_finish_entry", scope: !26, file: !19, line: 68, baseType: !29, size: 64, align: 64, offset: 192)
!39 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data", scope: !26, file: !19, line: 69, baseType: !40, size: 64, align: 64, offset: 256)
!40 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !41, size: 64, align: 64)
!41 = !DISubroutineType(types: !42)
!42 = !{!43, !17, !48, !50}
!43 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !44, line: 109, baseType: !45)
!44 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!45 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ssize_t", file: !46, line: 172, baseType: !47)
!46 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!47 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!48 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !49, size: 64, align: 64)
!49 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!50 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !51, line: 62, baseType: !52)
!51 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!52 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!53 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data_block", scope: !26, file: !19, line: 71, baseType: !54, size: 64, align: 64, offset: 320)
!54 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !55, size: 64, align: 64)
!55 = !DISubroutineType(types: !56)
!56 = !{!43, !17, !48, !50, !57}
!57 = !DIDerivedType(tag: DW_TAG_typedef, name: "int64_t", file: !58, line: 40, baseType: !47)
!58 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!59 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header", scope: !26, file: !19, line: 74, baseType: !60, size: 64, align: 64, offset: 384)
!60 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !61, size: 64, align: 64)
!61 = !DISubroutineType(types: !62)
!62 = !{!16, !17, !63}
!63 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !35, size: 64, align: 64)
!64 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header2", scope: !26, file: !19, line: 76, baseType: !32, size: 64, align: 64, offset: 448)
!65 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_data_block", scope: !26, file: !19, line: 78, baseType: !66, size: 64, align: 64, offset: 512)
!66 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !67, size: 64, align: 64)
!67 = !DISubroutineType(types: !68)
!68 = !{!16, !17, !69, !70, !71}
!69 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !48, size: 64, align: 64)
!70 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !50, size: 64, align: 64)
!71 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !57, size: 64, align: 64)
!72 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_count", scope: !26, file: !19, line: 81, baseType: !29, size: 64, align: 64, offset: 576)
!73 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_bytes", scope: !26, file: !19, line: 82, baseType: !74, size: 64, align: 64, offset: 640)
!74 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !75, size: 64, align: 64)
!75 = !DISubroutineType(types: !76)
!76 = !{!57, !17, !16}
!77 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_code", scope: !26, file: !19, line: 83, baseType: !78, size: 64, align: 64, offset: 704)
!78 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !79, size: 64, align: 64)
!79 = !DISubroutineType(types: !80)
!80 = !{!16, !17, !16}
!81 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_name", scope: !26, file: !19, line: 84, baseType: !82, size: 64, align: 64, offset: 768)
!82 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !83, size: 64, align: 64)
!83 = !DISubroutineType(types: !84)
!84 = !{!85, !17, !16}
!85 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !86, size: 64, align: 64)
!86 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !87)
!87 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!88 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format", scope: !18, file: !19, line: 105, baseType: !16, size: 32, align: 32, offset: 128)
!89 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format_name", scope: !18, file: !19, line: 106, baseType: !85, size: 64, align: 64, offset: 192)
!90 = !DIDerivedType(tag: DW_TAG_member, name: "compression_code", scope: !18, file: !19, line: 108, baseType: !16, size: 32, align: 32, offset: 256)
!91 = !DIDerivedType(tag: DW_TAG_member, name: "compression_name", scope: !18, file: !19, line: 109, baseType: !85, size: 64, align: 64, offset: 320)
!92 = !DIDerivedType(tag: DW_TAG_member, name: "file_count", scope: !18, file: !19, line: 112, baseType: !16, size: 32, align: 32, offset: 384)
!93 = !DIDerivedType(tag: DW_TAG_member, name: "archive_error_number", scope: !18, file: !19, line: 114, baseType: !16, size: 32, align: 32, offset: 416)
!94 = !DIDerivedType(tag: DW_TAG_member, name: "error", scope: !18, file: !19, line: 115, baseType: !85, size: 64, align: 64, offset: 448)
!95 = !DIDerivedType(tag: DW_TAG_member, name: "error_string", scope: !18, file: !19, line: 116, baseType: !96, size: 192, align: 64, offset: 512)
!96 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string", file: !97, line: 58, size: 192, align: 64, elements: !98)
!97 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_string.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!98 = !{!99, !101, !102}
!99 = !DIDerivedType(tag: DW_TAG_member, name: "s", scope: !96, file: !97, line: 59, baseType: !100, size: 64, align: 64)
!100 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !87, size: 64, align: 64)
!101 = !DIDerivedType(tag: DW_TAG_member, name: "length", scope: !96, file: !97, line: 60, baseType: !50, size: 64, align: 64, offset: 64)
!102 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_length", scope: !96, file: !97, line: 61, baseType: !50, size: 64, align: 64, offset: 128)
!103 = !DIDerivedType(tag: DW_TAG_member, name: "current_code", scope: !18, file: !19, line: 118, baseType: !100, size: 64, align: 64, offset: 704)
!104 = !DIDerivedType(tag: DW_TAG_member, name: "current_codepage", scope: !18, file: !19, line: 119, baseType: !22, size: 32, align: 32, offset: 768)
!105 = !DIDerivedType(tag: DW_TAG_member, name: "current_oemcp", scope: !18, file: !19, line: 120, baseType: !22, size: 32, align: 32, offset: 800)
!106 = !DIDerivedType(tag: DW_TAG_member, name: "sconv", scope: !18, file: !19, line: 121, baseType: !107, size: 64, align: 64, offset: 832)
!107 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !108, size: 64, align: 64)
!108 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string_conv", file: !97, line: 70, flags: DIFlagFwdDecl)
!109 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_block", scope: !18, file: !19, line: 127, baseType: !85, size: 64, align: 64, offset: 896)
!110 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_offset", scope: !18, file: !19, line: 128, baseType: !57, size: 64, align: 64, offset: 960)
!111 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_output_offset", scope: !18, file: !19, line: 129, baseType: !57, size: 64, align: 64, offset: 1024)
!112 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_remaining", scope: !18, file: !19, line: 130, baseType: !50, size: 64, align: 64, offset: 1088)
!113 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_is_posix_read", scope: !18, file: !19, line: 137, baseType: !87, size: 8, align: 8, offset: 1152)
!114 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_requested", scope: !18, file: !19, line: 138, baseType: !50, size: 64, align: 64, offset: 1216)
!115 = distinct !DISubprogram(name: "archive_write_grzip_options", scope: !1, file: !1, line: 90, type: !116, isLocal: true, isDefinition: true, scopeLine: 92, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!116 = !DISubroutineType(types: !117)
!117 = !{!16, !118, !85, !85}
!118 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !119, size: 64, align: 64)
!119 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_write_filter", file: !11, line: 43, size: 768, align: 64, elements: !120)
!120 = !{!121, !122, !123, !124, !126, !130, !134, !135, !136, !137, !138, !139, !140}
!121 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_written", scope: !119, file: !11, line: 44, baseType: !57, size: 64, align: 64)
!122 = !DIDerivedType(tag: DW_TAG_member, name: "archive", scope: !119, file: !11, line: 45, baseType: !17, size: 64, align: 64, offset: 64)
!123 = !DIDerivedType(tag: DW_TAG_member, name: "next_filter", scope: !119, file: !11, line: 46, baseType: !118, size: 64, align: 64, offset: 128)
!124 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !119, file: !11, line: 47, baseType: !125, size: 64, align: 64, offset: 192)
!125 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !116, size: 64, align: 64)
!126 = !DIDerivedType(tag: DW_TAG_member, name: "open", scope: !119, file: !11, line: 49, baseType: !127, size: 64, align: 64, offset: 256)
!127 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !128, size: 64, align: 64)
!128 = !DISubroutineType(types: !129)
!129 = !{!16, !118}
!130 = !DIDerivedType(tag: DW_TAG_member, name: "write", scope: !119, file: !11, line: 50, baseType: !131, size: 64, align: 64, offset: 320)
!131 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !132, size: 64, align: 64)
!132 = !DISubroutineType(types: !133)
!133 = !{!16, !118, !48, !50}
!134 = !DIDerivedType(tag: DW_TAG_member, name: "close", scope: !119, file: !11, line: 51, baseType: !127, size: 64, align: 64, offset: 384)
!135 = !DIDerivedType(tag: DW_TAG_member, name: "free", scope: !119, file: !11, line: 52, baseType: !127, size: 64, align: 64, offset: 448)
!136 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !119, file: !11, line: 53, baseType: !4, size: 64, align: 64, offset: 512)
!137 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !119, file: !11, line: 54, baseType: !85, size: 64, align: 64, offset: 576)
!138 = !DIDerivedType(tag: DW_TAG_member, name: "code", scope: !119, file: !11, line: 55, baseType: !16, size: 32, align: 32, offset: 640)
!139 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_per_block", scope: !119, file: !11, line: 56, baseType: !16, size: 32, align: 32, offset: 672)
!140 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_in_last_block", scope: !119, file: !11, line: 57, baseType: !16, size: 32, align: 32, offset: 704)
!141 = distinct !DISubprogram(name: "archive_write_grzip_open", scope: !1, file: !1, line: 103, type: !128, isLocal: true, isDefinition: true, scopeLine: 104, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!142 = distinct !DISubprogram(name: "archive_write_grzip_write", scope: !1, file: !1, line: 111, type: !132, isLocal: true, isDefinition: true, scopeLine: 113, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!143 = distinct !DISubprogram(name: "archive_write_grzip_close", scope: !1, file: !1, line: 120, type: !128, isLocal: true, isDefinition: true, scopeLine: 121, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!144 = distinct !DISubprogram(name: "archive_write_grzip_free", scope: !1, file: !1, line: 128, type: !128, isLocal: true, isDefinition: true, scopeLine: 129, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!145 = !{i32 2, !"Dwarf Version", i32 4}
!146 = !{i32 2, !"Debug Info Version", i32 3}
!147 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!148 = !DILocalVariable(name: "_a", arg: 1, scope: !13, file: !1, line: 53, type: !17)
!149 = !DIExpression()
!150 = !DILocation(line: 53, column: 48, scope: !13)
!151 = !DILocalVariable(name: "f", scope: !13, file: !1, line: 55, type: !118)
!152 = !DILocation(line: 55, column: 31, scope: !13)
!153 = !DILocation(line: 55, column: 67, scope: !13)
!154 = !DILocation(line: 55, column: 35, scope: !13)
!155 = !DILocalVariable(name: "data", scope: !13, file: !1, line: 56, type: !5)
!156 = !DILocation(line: 56, column: 22, scope: !13)
!157 = !DILocation(line: 58, column: 2, scope: !13)
!158 = !DILocalVariable(name: "magic_test", scope: !159, file: !1, line: 58, type: !16)
!159 = distinct !DILexicalBlock(scope: !13, file: !1, line: 58, column: 2)
!160 = !DILocation(line: 58, column: 2, scope: !159)
!161 = !DILocation(line: 58, column: 2, scope: !162)
!162 = !DILexicalBlockFile(scope: !159, file: !1, discriminator: 1)
!163 = !DILocation(line: 58, column: 2, scope: !164)
!164 = !DILexicalBlockFile(scope: !165, file: !1, discriminator: 2)
!165 = distinct !DILexicalBlock(scope: !159, file: !1, line: 58, column: 2)
!166 = !DILocation(line: 58, column: 2, scope: !167)
!167 = !DILexicalBlockFile(scope: !159, file: !1, discriminator: 3)
!168 = !DILocation(line: 61, column: 9, scope: !13)
!169 = !DILocation(line: 61, column: 7, scope: !13)
!170 = !DILocation(line: 62, column: 6, scope: !171)
!171 = distinct !DILexicalBlock(scope: !13, file: !1, line: 62, column: 6)
!172 = !DILocation(line: 62, column: 11, scope: !171)
!173 = !DILocation(line: 62, column: 6, scope: !13)
!174 = !DILocation(line: 63, column: 21, scope: !175)
!175 = distinct !DILexicalBlock(scope: !171, file: !1, line: 62, column: 20)
!176 = !DILocation(line: 63, column: 3, scope: !175)
!177 = !DILocation(line: 64, column: 3, scope: !175)
!178 = !DILocation(line: 66, column: 16, scope: !13)
!179 = !DILocation(line: 66, column: 2, scope: !13)
!180 = !DILocation(line: 66, column: 8, scope: !13)
!181 = !DILocation(line: 66, column: 14, scope: !13)
!182 = !DILocation(line: 67, column: 6, scope: !183)
!183 = distinct !DILexicalBlock(scope: !13, file: !1, line: 67, column: 6)
!184 = !DILocation(line: 67, column: 12, scope: !183)
!185 = !DILocation(line: 67, column: 18, scope: !183)
!186 = !DILocation(line: 67, column: 6, scope: !13)
!187 = !DILocation(line: 68, column: 8, scope: !188)
!188 = distinct !DILexicalBlock(scope: !183, file: !1, line: 67, column: 27)
!189 = !DILocation(line: 68, column: 3, scope: !188)
!190 = !DILocation(line: 69, column: 21, scope: !188)
!191 = !DILocation(line: 69, column: 3, scope: !188)
!192 = !DILocation(line: 70, column: 3, scope: !188)
!193 = !DILocation(line: 73, column: 2, scope: !13)
!194 = !DILocation(line: 73, column: 5, scope: !13)
!195 = !DILocation(line: 73, column: 10, scope: !13)
!196 = !DILocation(line: 74, column: 2, scope: !13)
!197 = !DILocation(line: 74, column: 5, scope: !13)
!198 = !DILocation(line: 74, column: 10, scope: !13)
!199 = !DILocation(line: 75, column: 12, scope: !13)
!200 = !DILocation(line: 75, column: 2, scope: !13)
!201 = !DILocation(line: 75, column: 5, scope: !13)
!202 = !DILocation(line: 75, column: 10, scope: !13)
!203 = !DILocation(line: 76, column: 2, scope: !13)
!204 = !DILocation(line: 76, column: 5, scope: !13)
!205 = !DILocation(line: 76, column: 10, scope: !13)
!206 = !DILocation(line: 77, column: 2, scope: !13)
!207 = !DILocation(line: 77, column: 5, scope: !13)
!208 = !DILocation(line: 77, column: 13, scope: !13)
!209 = !DILocation(line: 78, column: 2, scope: !13)
!210 = !DILocation(line: 78, column: 5, scope: !13)
!211 = !DILocation(line: 78, column: 11, scope: !13)
!212 = !DILocation(line: 79, column: 2, scope: !13)
!213 = !DILocation(line: 79, column: 5, scope: !13)
!214 = !DILocation(line: 79, column: 11, scope: !13)
!215 = !DILocation(line: 80, column: 2, scope: !13)
!216 = !DILocation(line: 80, column: 5, scope: !13)
!217 = !DILocation(line: 80, column: 10, scope: !13)
!218 = !DILocation(line: 84, column: 20, scope: !13)
!219 = !DILocation(line: 84, column: 2, scope: !13)
!220 = !DILocation(line: 86, column: 2, scope: !13)
!221 = !DILocation(line: 87, column: 1, scope: !13)
!222 = !DILocalVariable(name: "f", arg: 1, scope: !141, file: !1, line: 103, type: !118)
!223 = !DILocation(line: 103, column: 55, scope: !141)
!224 = !DILocalVariable(name: "data", scope: !141, file: !1, line: 105, type: !5)
!225 = !DILocation(line: 105, column: 22, scope: !141)
!226 = !DILocation(line: 105, column: 51, scope: !141)
!227 = !DILocation(line: 105, column: 54, scope: !141)
!228 = !DILocation(line: 105, column: 29, scope: !141)
!229 = !DILocation(line: 107, column: 38, scope: !141)
!230 = !DILocation(line: 107, column: 41, scope: !141)
!231 = !DILocation(line: 107, column: 47, scope: !141)
!232 = !DILocation(line: 107, column: 9, scope: !141)
!233 = !DILocation(line: 107, column: 2, scope: !141)
!234 = !DILocalVariable(name: "f", arg: 1, scope: !115, file: !1, line: 90, type: !118)
!235 = !DILocation(line: 90, column: 58, scope: !115)
!236 = !DILocalVariable(name: "key", arg: 2, scope: !115, file: !1, line: 90, type: !85)
!237 = !DILocation(line: 90, column: 73, scope: !115)
!238 = !DILocalVariable(name: "value", arg: 3, scope: !115, file: !1, line: 91, type: !85)
!239 = !DILocation(line: 91, column: 17, scope: !115)
!240 = !DILocation(line: 93, column: 8, scope: !115)
!241 = !DILocation(line: 94, column: 8, scope: !115)
!242 = !DILocation(line: 95, column: 8, scope: !115)
!243 = !DILocation(line: 99, column: 2, scope: !115)
!244 = !DILocalVariable(name: "f", arg: 1, scope: !142, file: !1, line: 111, type: !118)
!245 = !DILocation(line: 111, column: 56, scope: !142)
!246 = !DILocalVariable(name: "buff", arg: 2, scope: !142, file: !1, line: 112, type: !48)
!247 = !DILocation(line: 112, column: 17, scope: !142)
!248 = !DILocalVariable(name: "length", arg: 3, scope: !142, file: !1, line: 112, type: !50)
!249 = !DILocation(line: 112, column: 30, scope: !142)
!250 = !DILocalVariable(name: "data", scope: !142, file: !1, line: 114, type: !5)
!251 = !DILocation(line: 114, column: 22, scope: !142)
!252 = !DILocation(line: 114, column: 51, scope: !142)
!253 = !DILocation(line: 114, column: 54, scope: !142)
!254 = !DILocation(line: 114, column: 29, scope: !142)
!255 = !DILocation(line: 116, column: 39, scope: !142)
!256 = !DILocation(line: 116, column: 42, scope: !142)
!257 = !DILocation(line: 116, column: 48, scope: !142)
!258 = !DILocation(line: 116, column: 55, scope: !142)
!259 = !DILocation(line: 116, column: 61, scope: !142)
!260 = !DILocation(line: 116, column: 9, scope: !142)
!261 = !DILocation(line: 116, column: 2, scope: !142)
!262 = !DILocalVariable(name: "f", arg: 1, scope: !143, file: !1, line: 120, type: !118)
!263 = !DILocation(line: 120, column: 56, scope: !143)
!264 = !DILocalVariable(name: "data", scope: !143, file: !1, line: 122, type: !5)
!265 = !DILocation(line: 122, column: 22, scope: !143)
!266 = !DILocation(line: 122, column: 51, scope: !143)
!267 = !DILocation(line: 122, column: 54, scope: !143)
!268 = !DILocation(line: 122, column: 29, scope: !143)
!269 = !DILocation(line: 124, column: 39, scope: !143)
!270 = !DILocation(line: 124, column: 42, scope: !143)
!271 = !DILocation(line: 124, column: 48, scope: !143)
!272 = !DILocation(line: 124, column: 9, scope: !143)
!273 = !DILocation(line: 124, column: 2, scope: !143)
!274 = !DILocalVariable(name: "f", arg: 1, scope: !144, file: !1, line: 128, type: !118)
!275 = !DILocation(line: 128, column: 55, scope: !144)
!276 = !DILocalVariable(name: "data", scope: !144, file: !1, line: 130, type: !5)
!277 = !DILocation(line: 130, column: 22, scope: !144)
!278 = !DILocation(line: 130, column: 51, scope: !144)
!279 = !DILocation(line: 130, column: 54, scope: !144)
!280 = !DILocation(line: 130, column: 29, scope: !144)
!281 = !DILocation(line: 132, column: 31, scope: !144)
!282 = !DILocation(line: 132, column: 37, scope: !144)
!283 = !DILocation(line: 132, column: 2, scope: !144)
!284 = !DILocation(line: 133, column: 7, scope: !144)
!285 = !DILocation(line: 133, column: 2, scope: !144)
!286 = !DILocation(line: 134, column: 2, scope: !144)
