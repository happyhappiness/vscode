; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_add_filter_lzop.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.archive = type { i32, i32, %struct.archive_vtable*, i32, i8*, i32, i8*, i32, i32, i8*, %struct.archive_string, i8*, i32, i32, %struct.archive_string_conv*, i8*, i64, i64, i64, i8, i64 }
%struct.archive_vtable = type { {}*, {}*, i32 (%struct.archive*, %struct.archive_entry*)*, {}*, i64 (%struct.archive*, i8*, i64)*, i64 (%struct.archive*, i8*, i64, i64)*, i32 (%struct.archive*, %struct.archive_entry**)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*, i8**, i64*, i64*)*, {}*, i64 (%struct.archive*, i32)*, i32 (%struct.archive*, i32)*, i8* (%struct.archive*, i32)* }
%struct.archive_entry = type opaque
%struct.archive_string = type { i8*, i64, i64 }
%struct.archive_string_conv = type opaque
%struct.archive_write_filter = type { i64, %struct.archive*, %struct.archive_write_filter*, i32 (%struct.archive_write_filter*, i8*, i8*)*, i32 (%struct.archive_write_filter*)*, i32 (%struct.archive_write_filter*, i8*, i64)*, i32 (%struct.archive_write_filter*)*, i32 (%struct.archive_write_filter*)*, i8*, i8*, i32, i32, i32 }
%struct.write_lzop = type { i32, %struct.archive_write_program_data* }
%struct.archive_write_program_data = type opaque

@.str = private unnamed_addr constant [30 x i8] c"archive_write_add_filter_lzop\00", align 1
@.str.1 = private unnamed_addr constant [22 x i8] c"Can't allocate memory\00", align 1
@.str.2 = private unnamed_addr constant [5 x i8] c"lzop\00", align 1
@.str.3 = private unnamed_addr constant [49 x i8] c"Using external lzop program for lzop compression\00", align 1
@.str.4 = private unnamed_addr constant [18 x i8] c"compression-level\00", align 1

; Function Attrs: nounwind uwtable
define i32 @archive_write_add_filter_lzop(%struct.archive* %_a) #0 !dbg !15 {
entry:
  %retval = alloca i32, align 4
  %_a.addr = alloca %struct.archive*, align 8
  %f = alloca %struct.archive_write_filter*, align 8
  %data = alloca %struct.write_lzop*, align 8
  %magic_test = alloca i32, align 4
  store %struct.archive* %_a, %struct.archive** %_a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %_a.addr, metadata !149, metadata !150), !dbg !151
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f, metadata !152, metadata !150), !dbg !153
  %0 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !154
  %call = call %struct.archive_write_filter* @__archive_write_allocate_filter(%struct.archive* %0), !dbg !155
  store %struct.archive_write_filter* %call, %struct.archive_write_filter** %f, align 8, !dbg !153
  call void @llvm.dbg.declare(metadata %struct.write_lzop** %data, metadata !156, metadata !150), !dbg !157
  br label %do.body, !dbg !158

do.body:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %magic_test, metadata !159, metadata !150), !dbg !161
  %1 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !162
  %call1 = call i32 @__archive_check_magic(%struct.archive* %1, i32 -1329217314, i32 1, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str, i32 0, i32 0)), !dbg !162
  store i32 %call1, i32* %magic_test, align 4, !dbg !162
  %2 = load i32, i32* %magic_test, align 4, !dbg !162
  %cmp = icmp eq i32 %2, -30, !dbg !162
  br i1 %cmp, label %if.then, label %if.end, !dbg !162

if.then:                                          ; preds = %do.body
  store i32 -30, i32* %retval, align 4, !dbg !164
  br label %return, !dbg !164

if.end:                                           ; preds = %do.body
  br label %do.end, !dbg !167

do.end:                                           ; preds = %if.end
  %call2 = call noalias i8* @calloc(i64 1, i64 16) #5, !dbg !169
  %3 = bitcast i8* %call2 to %struct.write_lzop*, !dbg !169
  store %struct.write_lzop* %3, %struct.write_lzop** %data, align 8, !dbg !170
  %4 = load %struct.write_lzop*, %struct.write_lzop** %data, align 8, !dbg !171
  %cmp3 = icmp eq %struct.write_lzop* %4, null, !dbg !173
  br i1 %cmp3, label %if.then4, label %if.end5, !dbg !174

if.then4:                                         ; preds = %do.end
  %5 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !175
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %5, i32 12, i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.1, i32 0, i32 0)), !dbg !177
  store i32 -30, i32* %retval, align 4, !dbg !178
  br label %return, !dbg !178

if.end5:                                          ; preds = %do.end
  %6 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !179
  %name = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %6, i32 0, i32 9, !dbg !180
  store i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.2, i32 0, i32 0), i8** %name, align 8, !dbg !181
  %7 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !182
  %code = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %7, i32 0, i32 10, !dbg !183
  store i32 11, i32* %code, align 8, !dbg !184
  %8 = load %struct.write_lzop*, %struct.write_lzop** %data, align 8, !dbg !185
  %9 = bitcast %struct.write_lzop* %8 to i8*, !dbg !185
  %10 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !186
  %data6 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %10, i32 0, i32 8, !dbg !187
  store i8* %9, i8** %data6, align 8, !dbg !188
  %11 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !189
  %open = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %11, i32 0, i32 4, !dbg !190
  store i32 (%struct.archive_write_filter*)* @archive_write_lzop_open, i32 (%struct.archive_write_filter*)** %open, align 8, !dbg !191
  %12 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !192
  %options = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %12, i32 0, i32 3, !dbg !193
  store i32 (%struct.archive_write_filter*, i8*, i8*)* @archive_write_lzop_options, i32 (%struct.archive_write_filter*, i8*, i8*)** %options, align 8, !dbg !194
  %13 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !195
  %write = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %13, i32 0, i32 5, !dbg !196
  store i32 (%struct.archive_write_filter*, i8*, i64)* @archive_write_lzop_write, i32 (%struct.archive_write_filter*, i8*, i64)** %write, align 8, !dbg !197
  %14 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !198
  %close = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %14, i32 0, i32 6, !dbg !199
  store i32 (%struct.archive_write_filter*)* @archive_write_lzop_close, i32 (%struct.archive_write_filter*)** %close, align 8, !dbg !200
  %15 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f, align 8, !dbg !201
  %free = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %15, i32 0, i32 7, !dbg !202
  store i32 (%struct.archive_write_filter*)* @archive_write_lzop_free, i32 (%struct.archive_write_filter*)** %free, align 8, !dbg !203
  %call7 = call %struct.archive_write_program_data* @__archive_write_program_allocate(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.2, i32 0, i32 0)), !dbg !204
  %16 = load %struct.write_lzop*, %struct.write_lzop** %data, align 8, !dbg !205
  %pdata = getelementptr inbounds %struct.write_lzop, %struct.write_lzop* %16, i32 0, i32 1, !dbg !206
  store %struct.archive_write_program_data* %call7, %struct.archive_write_program_data** %pdata, align 8, !dbg !207
  %17 = load %struct.write_lzop*, %struct.write_lzop** %data, align 8, !dbg !208
  %pdata8 = getelementptr inbounds %struct.write_lzop, %struct.write_lzop* %17, i32 0, i32 1, !dbg !210
  %18 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %pdata8, align 8, !dbg !210
  %cmp9 = icmp eq %struct.archive_write_program_data* %18, null, !dbg !211
  br i1 %cmp9, label %if.then10, label %if.end11, !dbg !212

if.then10:                                        ; preds = %if.end5
  %19 = load %struct.write_lzop*, %struct.write_lzop** %data, align 8, !dbg !213
  %20 = bitcast %struct.write_lzop* %19 to i8*, !dbg !213
  call void @free(i8* %20) #5, !dbg !215
  %21 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !216
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %21, i32 12, i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.1, i32 0, i32 0)), !dbg !217
  store i32 -30, i32* %retval, align 4, !dbg !218
  br label %return, !dbg !218

if.end11:                                         ; preds = %if.end5
  %22 = load %struct.write_lzop*, %struct.write_lzop** %data, align 8, !dbg !219
  %compression_level = getelementptr inbounds %struct.write_lzop, %struct.write_lzop* %22, i32 0, i32 0, !dbg !220
  store i32 0, i32* %compression_level, align 8, !dbg !221
  %23 = load %struct.archive*, %struct.archive** %_a.addr, align 8, !dbg !222
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %23, i32 -1, i8* getelementptr inbounds ([49 x i8], [49 x i8]* @.str.3, i32 0, i32 0)), !dbg !223
  store i32 -20, i32* %retval, align 4, !dbg !224
  br label %return, !dbg !224

return:                                           ; preds = %if.end11, %if.then10, %if.then4, %if.then
  %24 = load i32, i32* %retval, align 4, !dbg !225
  ret i32 %24, !dbg !225
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

declare %struct.archive_write_filter* @__archive_write_allocate_filter(%struct.archive*) #2

declare i32 @__archive_check_magic(%struct.archive*, i32, i32, i8*) #2

; Function Attrs: nounwind
declare noalias i8* @calloc(i64, i64) #3

declare void @archive_set_error(%struct.archive*, i32, i8*, ...) #2

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_lzop_open(%struct.archive_write_filter* %f) #0 !dbg !143 {
entry:
  %f.addr = alloca %struct.archive_write_filter*, align 8
  %data = alloca %struct.write_lzop*, align 8
  %as = alloca %struct.archive_string, align 8
  %r = alloca i32, align 4
  store %struct.archive_write_filter* %f, %struct.archive_write_filter** %f.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f.addr, metadata !226, metadata !150), !dbg !227
  call void @llvm.dbg.declare(metadata %struct.write_lzop** %data, metadata !228, metadata !150), !dbg !229
  %0 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !230
  %data1 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %0, i32 0, i32 8, !dbg !231
  %1 = load i8*, i8** %data1, align 8, !dbg !231
  %2 = bitcast i8* %1 to %struct.write_lzop*, !dbg !232
  store %struct.write_lzop* %2, %struct.write_lzop** %data, align 8, !dbg !229
  call void @llvm.dbg.declare(metadata %struct.archive_string* %as, metadata !233, metadata !150), !dbg !234
  call void @llvm.dbg.declare(metadata i32* %r, metadata !235, metadata !150), !dbg !236
  br label %do.body, !dbg !237

do.body:                                          ; preds = %entry
  %s = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 0, !dbg !238
  store i8* null, i8** %s, align 8, !dbg !238
  %length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 1, !dbg !238
  store i64 0, i64* %length, align 8, !dbg !238
  %buffer_length = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 2, !dbg !238
  store i64 0, i64* %buffer_length, align 8, !dbg !238
  br label %do.end, !dbg !238

do.end:                                           ; preds = %do.body
  %length2 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 1, !dbg !241
  store i64 0, i64* %length2, align 8, !dbg !241
  %call = call %struct.archive_string* @archive_strncat(%struct.archive_string* %as, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.2, i32 0, i32 0), i64 4), !dbg !241
  %3 = load %struct.write_lzop*, %struct.write_lzop** %data, align 8, !dbg !242
  %compression_level = getelementptr inbounds %struct.write_lzop, %struct.write_lzop* %3, i32 0, i32 0, !dbg !244
  %4 = load i32, i32* %compression_level, align 8, !dbg !244
  %cmp = icmp sgt i32 %4, 0, !dbg !245
  br i1 %cmp, label %if.then, label %if.end, !dbg !246

if.then:                                          ; preds = %do.end
  %call3 = call %struct.archive_string* @archive_strappend_char(%struct.archive_string* %as, i8 signext 32), !dbg !247
  %call4 = call %struct.archive_string* @archive_strappend_char(%struct.archive_string* %as, i8 signext 45), !dbg !249
  %5 = load %struct.write_lzop*, %struct.write_lzop** %data, align 8, !dbg !250
  %compression_level5 = getelementptr inbounds %struct.write_lzop, %struct.write_lzop* %5, i32 0, i32 0, !dbg !251
  %6 = load i32, i32* %compression_level5, align 8, !dbg !251
  %add = add nsw i32 48, %6, !dbg !252
  %conv = trunc i32 %add to i8, !dbg !253
  %call6 = call %struct.archive_string* @archive_strappend_char(%struct.archive_string* %as, i8 signext %conv), !dbg !254
  br label %if.end, !dbg !255

if.end:                                           ; preds = %if.then, %do.end
  %7 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !256
  %8 = load %struct.write_lzop*, %struct.write_lzop** %data, align 8, !dbg !257
  %pdata = getelementptr inbounds %struct.write_lzop, %struct.write_lzop* %8, i32 0, i32 1, !dbg !258
  %9 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %pdata, align 8, !dbg !258
  %s7 = getelementptr inbounds %struct.archive_string, %struct.archive_string* %as, i32 0, i32 0, !dbg !259
  %10 = load i8*, i8** %s7, align 8, !dbg !259
  %call8 = call i32 @__archive_write_program_open(%struct.archive_write_filter* %7, %struct.archive_write_program_data* %9, i8* %10), !dbg !260
  store i32 %call8, i32* %r, align 4, !dbg !261
  call void @archive_string_free(%struct.archive_string* %as), !dbg !262
  %11 = load i32, i32* %r, align 4, !dbg !263
  ret i32 %11, !dbg !264
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_lzop_options(%struct.archive_write_filter* %f, i8* %key, i8* %value) #0 !dbg !142 {
entry:
  %retval = alloca i32, align 4
  %f.addr = alloca %struct.archive_write_filter*, align 8
  %key.addr = alloca i8*, align 8
  %value.addr = alloca i8*, align 8
  %data = alloca %struct.write_lzop*, align 8
  store %struct.archive_write_filter* %f, %struct.archive_write_filter** %f.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f.addr, metadata !265, metadata !150), !dbg !266
  store i8* %key, i8** %key.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %key.addr, metadata !267, metadata !150), !dbg !268
  store i8* %value, i8** %value.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %value.addr, metadata !269, metadata !150), !dbg !270
  call void @llvm.dbg.declare(metadata %struct.write_lzop** %data, metadata !271, metadata !150), !dbg !272
  %0 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !273
  %data1 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %0, i32 0, i32 8, !dbg !274
  %1 = load i8*, i8** %data1, align 8, !dbg !274
  %2 = bitcast i8* %1 to %struct.write_lzop*, !dbg !275
  store %struct.write_lzop* %2, %struct.write_lzop** %data, align 8, !dbg !272
  %3 = load i8*, i8** %key.addr, align 8, !dbg !276
  %call = call i32 @strcmp(i8* %3, i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.4, i32 0, i32 0)) #6, !dbg !278
  %cmp = icmp eq i32 %call, 0, !dbg !279
  br i1 %cmp, label %if.then, label %if.end17, !dbg !280

if.then:                                          ; preds = %entry
  %4 = load i8*, i8** %value.addr, align 8, !dbg !281
  %cmp2 = icmp eq i8* %4, null, !dbg !284
  br i1 %cmp2, label %if.then14, label %lor.lhs.false, !dbg !285

lor.lhs.false:                                    ; preds = %if.then
  %5 = load i8*, i8** %value.addr, align 8, !dbg !286
  %arrayidx = getelementptr inbounds i8, i8* %5, i64 0, !dbg !286
  %6 = load i8, i8* %arrayidx, align 1, !dbg !286
  %conv = sext i8 %6 to i32, !dbg !286
  %cmp3 = icmp sge i32 %conv, 49, !dbg !288
  br i1 %cmp3, label %land.lhs.true, label %if.then14, !dbg !289

land.lhs.true:                                    ; preds = %lor.lhs.false
  %7 = load i8*, i8** %value.addr, align 8, !dbg !290
  %arrayidx5 = getelementptr inbounds i8, i8* %7, i64 0, !dbg !290
  %8 = load i8, i8* %arrayidx5, align 1, !dbg !290
  %conv6 = sext i8 %8 to i32, !dbg !290
  %cmp7 = icmp sle i32 %conv6, 57, !dbg !292
  br i1 %cmp7, label %lor.lhs.false9, label %if.then14, !dbg !293

lor.lhs.false9:                                   ; preds = %land.lhs.true
  %9 = load i8*, i8** %value.addr, align 8, !dbg !294
  %arrayidx10 = getelementptr inbounds i8, i8* %9, i64 1, !dbg !294
  %10 = load i8, i8* %arrayidx10, align 1, !dbg !294
  %conv11 = sext i8 %10 to i32, !dbg !294
  %cmp12 = icmp ne i32 %conv11, 0, !dbg !295
  br i1 %cmp12, label %if.then14, label %if.end, !dbg !296

if.then14:                                        ; preds = %lor.lhs.false9, %land.lhs.true, %lor.lhs.false, %if.then
  store i32 -20, i32* %retval, align 4, !dbg !298
  br label %return, !dbg !298

if.end:                                           ; preds = %lor.lhs.false9
  %11 = load i8*, i8** %value.addr, align 8, !dbg !299
  %arrayidx15 = getelementptr inbounds i8, i8* %11, i64 0, !dbg !299
  %12 = load i8, i8* %arrayidx15, align 1, !dbg !299
  %conv16 = sext i8 %12 to i32, !dbg !299
  %sub = sub nsw i32 %conv16, 48, !dbg !300
  %13 = load %struct.write_lzop*, %struct.write_lzop** %data, align 8, !dbg !301
  %compression_level = getelementptr inbounds %struct.write_lzop, %struct.write_lzop* %13, i32 0, i32 0, !dbg !302
  store i32 %sub, i32* %compression_level, align 8, !dbg !303
  store i32 0, i32* %retval, align 4, !dbg !304
  br label %return, !dbg !304

if.end17:                                         ; preds = %entry
  store i32 -20, i32* %retval, align 4, !dbg !305
  br label %return, !dbg !305

return:                                           ; preds = %if.end17, %if.end, %if.then14
  %14 = load i32, i32* %retval, align 4, !dbg !306
  ret i32 %14, !dbg !306
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_lzop_write(%struct.archive_write_filter* %f, i8* %buff, i64 %length) #0 !dbg !144 {
entry:
  %f.addr = alloca %struct.archive_write_filter*, align 8
  %buff.addr = alloca i8*, align 8
  %length.addr = alloca i64, align 8
  %data = alloca %struct.write_lzop*, align 8
  store %struct.archive_write_filter* %f, %struct.archive_write_filter** %f.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f.addr, metadata !307, metadata !150), !dbg !308
  store i8* %buff, i8** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buff.addr, metadata !309, metadata !150), !dbg !310
  store i64 %length, i64* %length.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %length.addr, metadata !311, metadata !150), !dbg !312
  call void @llvm.dbg.declare(metadata %struct.write_lzop** %data, metadata !313, metadata !150), !dbg !314
  %0 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !315
  %data1 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %0, i32 0, i32 8, !dbg !316
  %1 = load i8*, i8** %data1, align 8, !dbg !316
  %2 = bitcast i8* %1 to %struct.write_lzop*, !dbg !317
  store %struct.write_lzop* %2, %struct.write_lzop** %data, align 8, !dbg !314
  %3 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !318
  %4 = load %struct.write_lzop*, %struct.write_lzop** %data, align 8, !dbg !319
  %pdata = getelementptr inbounds %struct.write_lzop, %struct.write_lzop* %4, i32 0, i32 1, !dbg !320
  %5 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %pdata, align 8, !dbg !320
  %6 = load i8*, i8** %buff.addr, align 8, !dbg !321
  %7 = load i64, i64* %length.addr, align 8, !dbg !322
  %call = call i32 @__archive_write_program_write(%struct.archive_write_filter* %3, %struct.archive_write_program_data* %5, i8* %6, i64 %7), !dbg !323
  ret i32 %call, !dbg !324
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_lzop_close(%struct.archive_write_filter* %f) #0 !dbg !145 {
entry:
  %f.addr = alloca %struct.archive_write_filter*, align 8
  %data = alloca %struct.write_lzop*, align 8
  store %struct.archive_write_filter* %f, %struct.archive_write_filter** %f.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f.addr, metadata !325, metadata !150), !dbg !326
  call void @llvm.dbg.declare(metadata %struct.write_lzop** %data, metadata !327, metadata !150), !dbg !328
  %0 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !329
  %data1 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %0, i32 0, i32 8, !dbg !330
  %1 = load i8*, i8** %data1, align 8, !dbg !330
  %2 = bitcast i8* %1 to %struct.write_lzop*, !dbg !331
  store %struct.write_lzop* %2, %struct.write_lzop** %data, align 8, !dbg !328
  %3 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !332
  %4 = load %struct.write_lzop*, %struct.write_lzop** %data, align 8, !dbg !333
  %pdata = getelementptr inbounds %struct.write_lzop, %struct.write_lzop* %4, i32 0, i32 1, !dbg !334
  %5 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %pdata, align 8, !dbg !334
  %call = call i32 @__archive_write_program_close(%struct.archive_write_filter* %3, %struct.archive_write_program_data* %5), !dbg !335
  ret i32 %call, !dbg !336
}

; Function Attrs: nounwind uwtable
define internal i32 @archive_write_lzop_free(%struct.archive_write_filter* %f) #0 !dbg !116 {
entry:
  %f.addr = alloca %struct.archive_write_filter*, align 8
  %data = alloca %struct.write_lzop*, align 8
  store %struct.archive_write_filter* %f, %struct.archive_write_filter** %f.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_write_filter** %f.addr, metadata !337, metadata !150), !dbg !338
  call void @llvm.dbg.declare(metadata %struct.write_lzop** %data, metadata !339, metadata !150), !dbg !340
  %0 = load %struct.archive_write_filter*, %struct.archive_write_filter** %f.addr, align 8, !dbg !341
  %data1 = getelementptr inbounds %struct.archive_write_filter, %struct.archive_write_filter* %0, i32 0, i32 8, !dbg !342
  %1 = load i8*, i8** %data1, align 8, !dbg !342
  %2 = bitcast i8* %1 to %struct.write_lzop*, !dbg !343
  store %struct.write_lzop* %2, %struct.write_lzop** %data, align 8, !dbg !340
  %3 = load %struct.write_lzop*, %struct.write_lzop** %data, align 8, !dbg !344
  %pdata = getelementptr inbounds %struct.write_lzop, %struct.write_lzop* %3, i32 0, i32 1, !dbg !345
  %4 = load %struct.archive_write_program_data*, %struct.archive_write_program_data** %pdata, align 8, !dbg !345
  %call = call i32 @__archive_write_program_free(%struct.archive_write_program_data* %4), !dbg !346
  %5 = load %struct.write_lzop*, %struct.write_lzop** %data, align 8, !dbg !347
  %6 = bitcast %struct.write_lzop* %5 to i8*, !dbg !347
  call void @free(i8* %6) #5, !dbg !348
  ret i32 0, !dbg !349
}

declare %struct.archive_write_program_data* @__archive_write_program_allocate(i8*) #2

; Function Attrs: nounwind
declare void @free(i8*) #3

declare i32 @__archive_write_program_free(%struct.archive_write_program_data*) #2

; Function Attrs: nounwind readonly
declare i32 @strcmp(i8*, i8*) #4

declare %struct.archive_string* @archive_strncat(%struct.archive_string*, i8*, i64) #2

declare %struct.archive_string* @archive_strappend_char(%struct.archive_string*, i8 signext) #2

declare i32 @__archive_write_program_open(%struct.archive_write_filter*, %struct.archive_write_program_data*, i8*) #2

declare void @archive_string_free(%struct.archive_string*) #2

declare i32 @__archive_write_program_write(%struct.archive_write_filter*, %struct.archive_write_program_data*, i8*, i64) #2

declare i32 @__archive_write_program_close(%struct.archive_write_filter*, %struct.archive_write_program_data*) #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind }
attributes #6 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!146, !147}
!llvm.ident = !{!148}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !14)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_add_filter_lzop.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4, !5}
!4 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!5 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !6, size: 64, align: 64)
!6 = !DICompositeType(tag: DW_TAG_structure_type, name: "write_lzop", file: !1, line: 59, size: 128, align: 64, elements: !7)
!7 = !{!8, !10}
!8 = !DIDerivedType(tag: DW_TAG_member, name: "compression_level", scope: !6, file: !1, line: 60, baseType: !9, size: 32, align: 32)
!9 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!10 = !DIDerivedType(tag: DW_TAG_member, name: "pdata", scope: !6, file: !1, line: 73, baseType: !11, size: 64, align: 64, offset: 64)
!11 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !12, size: 64, align: 64)
!12 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_write_program_data", file: !13, line: 146, flags: DIFlagFwdDecl)
!13 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!14 = !{!15, !116, !142, !143, !144, !145}
!15 = distinct !DISubprogram(name: "archive_write_add_filter_lzop", scope: !1, file: !1, line: 137, type: !16, isLocal: false, isDefinition: true, scopeLine: 138, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!16 = !DISubroutineType(types: !17)
!17 = !{!9, !18}
!18 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !19, size: 64, align: 64)
!19 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive", file: !20, line: 89, size: 1280, align: 64, elements: !21)
!20 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!21 = !{!22, !24, !25, !89, !90, !91, !92, !93, !94, !95, !96, !104, !105, !106, !107, !110, !111, !112, !113, !114, !115}
!22 = !DIDerivedType(tag: DW_TAG_member, name: "magic", scope: !19, file: !20, line: 96, baseType: !23, size: 32, align: 32)
!23 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!24 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !19, file: !20, line: 97, baseType: !23, size: 32, align: 32, offset: 32)
!25 = !DIDerivedType(tag: DW_TAG_member, name: "vtable", scope: !19, file: !20, line: 103, baseType: !26, size: 64, align: 64, offset: 64)
!26 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !27, size: 64, align: 64)
!27 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_vtable", file: !20, line: 63, size: 832, align: 64, elements: !28)
!28 = !{!29, !31, !32, !39, !40, !54, !60, !65, !66, !73, !74, !78, !82}
!29 = !DIDerivedType(tag: DW_TAG_member, name: "archive_close", scope: !27, file: !20, line: 64, baseType: !30, size: 64, align: 64)
!30 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !16, size: 64, align: 64)
!31 = !DIDerivedType(tag: DW_TAG_member, name: "archive_free", scope: !27, file: !20, line: 65, baseType: !30, size: 64, align: 64, offset: 64)
!32 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_header", scope: !27, file: !20, line: 66, baseType: !33, size: 64, align: 64, offset: 128)
!33 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !34, size: 64, align: 64)
!34 = !DISubroutineType(types: !35)
!35 = !{!9, !18, !36}
!36 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !37, size: 64, align: 64)
!37 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_entry", file: !38, line: 180, flags: DIFlagFwdDecl)
!38 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!39 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_finish_entry", scope: !27, file: !20, line: 68, baseType: !30, size: 64, align: 64, offset: 192)
!40 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data", scope: !27, file: !20, line: 69, baseType: !41, size: 64, align: 64, offset: 256)
!41 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !42, size: 64, align: 64)
!42 = !DISubroutineType(types: !43)
!43 = !{!44, !18, !49, !51}
!44 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !45, line: 109, baseType: !46)
!45 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!46 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ssize_t", file: !47, line: 172, baseType: !48)
!47 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!48 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!49 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !50, size: 64, align: 64)
!50 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!51 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !52, line: 62, baseType: !53)
!52 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!53 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!54 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data_block", scope: !27, file: !20, line: 71, baseType: !55, size: 64, align: 64, offset: 320)
!55 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !56, size: 64, align: 64)
!56 = !DISubroutineType(types: !57)
!57 = !{!44, !18, !49, !51, !58}
!58 = !DIDerivedType(tag: DW_TAG_typedef, name: "int64_t", file: !59, line: 40, baseType: !48)
!59 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!60 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header", scope: !27, file: !20, line: 74, baseType: !61, size: 64, align: 64, offset: 384)
!61 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !62, size: 64, align: 64)
!62 = !DISubroutineType(types: !63)
!63 = !{!9, !18, !64}
!64 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !36, size: 64, align: 64)
!65 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header2", scope: !27, file: !20, line: 76, baseType: !33, size: 64, align: 64, offset: 448)
!66 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_data_block", scope: !27, file: !20, line: 78, baseType: !67, size: 64, align: 64, offset: 512)
!67 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !68, size: 64, align: 64)
!68 = !DISubroutineType(types: !69)
!69 = !{!9, !18, !70, !71, !72}
!70 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !49, size: 64, align: 64)
!71 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !51, size: 64, align: 64)
!72 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !58, size: 64, align: 64)
!73 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_count", scope: !27, file: !20, line: 81, baseType: !30, size: 64, align: 64, offset: 576)
!74 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_bytes", scope: !27, file: !20, line: 82, baseType: !75, size: 64, align: 64, offset: 640)
!75 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !76, size: 64, align: 64)
!76 = !DISubroutineType(types: !77)
!77 = !{!58, !18, !9}
!78 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_code", scope: !27, file: !20, line: 83, baseType: !79, size: 64, align: 64, offset: 704)
!79 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !80, size: 64, align: 64)
!80 = !DISubroutineType(types: !81)
!81 = !{!9, !18, !9}
!82 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_name", scope: !27, file: !20, line: 84, baseType: !83, size: 64, align: 64, offset: 768)
!83 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !84, size: 64, align: 64)
!84 = !DISubroutineType(types: !85)
!85 = !{!86, !18, !9}
!86 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !87, size: 64, align: 64)
!87 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !88)
!88 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!89 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format", scope: !19, file: !20, line: 105, baseType: !9, size: 32, align: 32, offset: 128)
!90 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format_name", scope: !19, file: !20, line: 106, baseType: !86, size: 64, align: 64, offset: 192)
!91 = !DIDerivedType(tag: DW_TAG_member, name: "compression_code", scope: !19, file: !20, line: 108, baseType: !9, size: 32, align: 32, offset: 256)
!92 = !DIDerivedType(tag: DW_TAG_member, name: "compression_name", scope: !19, file: !20, line: 109, baseType: !86, size: 64, align: 64, offset: 320)
!93 = !DIDerivedType(tag: DW_TAG_member, name: "file_count", scope: !19, file: !20, line: 112, baseType: !9, size: 32, align: 32, offset: 384)
!94 = !DIDerivedType(tag: DW_TAG_member, name: "archive_error_number", scope: !19, file: !20, line: 114, baseType: !9, size: 32, align: 32, offset: 416)
!95 = !DIDerivedType(tag: DW_TAG_member, name: "error", scope: !19, file: !20, line: 115, baseType: !86, size: 64, align: 64, offset: 448)
!96 = !DIDerivedType(tag: DW_TAG_member, name: "error_string", scope: !19, file: !20, line: 116, baseType: !97, size: 192, align: 64, offset: 512)
!97 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string", file: !98, line: 58, size: 192, align: 64, elements: !99)
!98 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_string.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!99 = !{!100, !102, !103}
!100 = !DIDerivedType(tag: DW_TAG_member, name: "s", scope: !97, file: !98, line: 59, baseType: !101, size: 64, align: 64)
!101 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !88, size: 64, align: 64)
!102 = !DIDerivedType(tag: DW_TAG_member, name: "length", scope: !97, file: !98, line: 60, baseType: !51, size: 64, align: 64, offset: 64)
!103 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_length", scope: !97, file: !98, line: 61, baseType: !51, size: 64, align: 64, offset: 128)
!104 = !DIDerivedType(tag: DW_TAG_member, name: "current_code", scope: !19, file: !20, line: 118, baseType: !101, size: 64, align: 64, offset: 704)
!105 = !DIDerivedType(tag: DW_TAG_member, name: "current_codepage", scope: !19, file: !20, line: 119, baseType: !23, size: 32, align: 32, offset: 768)
!106 = !DIDerivedType(tag: DW_TAG_member, name: "current_oemcp", scope: !19, file: !20, line: 120, baseType: !23, size: 32, align: 32, offset: 800)
!107 = !DIDerivedType(tag: DW_TAG_member, name: "sconv", scope: !19, file: !20, line: 121, baseType: !108, size: 64, align: 64, offset: 832)
!108 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !109, size: 64, align: 64)
!109 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string_conv", file: !98, line: 70, flags: DIFlagFwdDecl)
!110 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_block", scope: !19, file: !20, line: 127, baseType: !86, size: 64, align: 64, offset: 896)
!111 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_offset", scope: !19, file: !20, line: 128, baseType: !58, size: 64, align: 64, offset: 960)
!112 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_output_offset", scope: !19, file: !20, line: 129, baseType: !58, size: 64, align: 64, offset: 1024)
!113 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_remaining", scope: !19, file: !20, line: 130, baseType: !51, size: 64, align: 64, offset: 1088)
!114 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_is_posix_read", scope: !19, file: !20, line: 137, baseType: !88, size: 8, align: 8, offset: 1152)
!115 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_requested", scope: !19, file: !20, line: 138, baseType: !51, size: 64, align: 64, offset: 1216)
!116 = distinct !DISubprogram(name: "archive_write_lzop_free", scope: !1, file: !1, line: 192, type: !117, isLocal: true, isDefinition: true, scopeLine: 193, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!117 = !DISubroutineType(types: !118)
!118 = !{!9, !119}
!119 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !120, size: 64, align: 64)
!120 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_write_filter", file: !13, line: 43, size: 768, align: 64, elements: !121)
!121 = !{!122, !123, !124, !125, !129, !131, !135, !136, !137, !138, !139, !140, !141}
!122 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_written", scope: !120, file: !13, line: 44, baseType: !58, size: 64, align: 64)
!123 = !DIDerivedType(tag: DW_TAG_member, name: "archive", scope: !120, file: !13, line: 45, baseType: !18, size: 64, align: 64, offset: 64)
!124 = !DIDerivedType(tag: DW_TAG_member, name: "next_filter", scope: !120, file: !13, line: 46, baseType: !119, size: 64, align: 64, offset: 128)
!125 = !DIDerivedType(tag: DW_TAG_member, name: "options", scope: !120, file: !13, line: 47, baseType: !126, size: 64, align: 64, offset: 192)
!126 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !127, size: 64, align: 64)
!127 = !DISubroutineType(types: !128)
!128 = !{!9, !119, !86, !86}
!129 = !DIDerivedType(tag: DW_TAG_member, name: "open", scope: !120, file: !13, line: 49, baseType: !130, size: 64, align: 64, offset: 256)
!130 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !117, size: 64, align: 64)
!131 = !DIDerivedType(tag: DW_TAG_member, name: "write", scope: !120, file: !13, line: 50, baseType: !132, size: 64, align: 64, offset: 320)
!132 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !133, size: 64, align: 64)
!133 = !DISubroutineType(types: !134)
!134 = !{!9, !119, !49, !51}
!135 = !DIDerivedType(tag: DW_TAG_member, name: "close", scope: !120, file: !13, line: 51, baseType: !130, size: 64, align: 64, offset: 384)
!136 = !DIDerivedType(tag: DW_TAG_member, name: "free", scope: !120, file: !13, line: 52, baseType: !130, size: 64, align: 64, offset: 448)
!137 = !DIDerivedType(tag: DW_TAG_member, name: "data", scope: !120, file: !13, line: 53, baseType: !4, size: 64, align: 64, offset: 512)
!138 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !120, file: !13, line: 54, baseType: !86, size: 64, align: 64, offset: 576)
!139 = !DIDerivedType(tag: DW_TAG_member, name: "code", scope: !120, file: !13, line: 55, baseType: !9, size: 32, align: 32, offset: 640)
!140 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_per_block", scope: !120, file: !13, line: 56, baseType: !9, size: 32, align: 32, offset: 672)
!141 = !DIDerivedType(tag: DW_TAG_member, name: "bytes_in_last_block", scope: !120, file: !13, line: 57, baseType: !9, size: 32, align: 32, offset: 704)
!142 = distinct !DISubprogram(name: "archive_write_lzop_options", scope: !1, file: !1, line: 208, type: !127, isLocal: true, isDefinition: true, scopeLine: 210, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!143 = distinct !DISubprogram(name: "archive_write_lzop_open", scope: !1, file: !1, line: 450, type: !117, isLocal: true, isDefinition: true, scopeLine: 451, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!144 = distinct !DISubprogram(name: "archive_write_lzop_write", scope: !1, file: !1, line: 471, type: !133, isLocal: true, isDefinition: true, scopeLine: 473, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!145 = distinct !DISubprogram(name: "archive_write_lzop_close", scope: !1, file: !1, line: 480, type: !117, isLocal: true, isDefinition: true, scopeLine: 481, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!146 = !{i32 2, !"Dwarf Version", i32 4}
!147 = !{i32 2, !"Debug Info Version", i32 3}
!148 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!149 = !DILocalVariable(name: "_a", arg: 1, scope: !15, file: !1, line: 137, type: !18)
!150 = !DIExpression()
!151 = !DILocation(line: 137, column: 47, scope: !15)
!152 = !DILocalVariable(name: "f", scope: !15, file: !1, line: 139, type: !119)
!153 = !DILocation(line: 139, column: 31, scope: !15)
!154 = !DILocation(line: 139, column: 67, scope: !15)
!155 = !DILocation(line: 139, column: 35, scope: !15)
!156 = !DILocalVariable(name: "data", scope: !15, file: !1, line: 140, type: !5)
!157 = !DILocation(line: 140, column: 21, scope: !15)
!158 = !DILocation(line: 142, column: 2, scope: !15)
!159 = !DILocalVariable(name: "magic_test", scope: !160, file: !1, line: 142, type: !9)
!160 = distinct !DILexicalBlock(scope: !15, file: !1, line: 142, column: 2)
!161 = !DILocation(line: 142, column: 2, scope: !160)
!162 = !DILocation(line: 142, column: 2, scope: !163)
!163 = !DILexicalBlockFile(scope: !160, file: !1, discriminator: 1)
!164 = !DILocation(line: 142, column: 2, scope: !165)
!165 = !DILexicalBlockFile(scope: !166, file: !1, discriminator: 2)
!166 = distinct !DILexicalBlock(scope: !160, file: !1, line: 142, column: 2)
!167 = !DILocation(line: 142, column: 2, scope: !168)
!168 = !DILexicalBlockFile(scope: !160, file: !1, discriminator: 3)
!169 = !DILocation(line: 145, column: 9, scope: !15)
!170 = !DILocation(line: 145, column: 7, scope: !15)
!171 = !DILocation(line: 146, column: 6, scope: !172)
!172 = distinct !DILexicalBlock(scope: !15, file: !1, line: 146, column: 6)
!173 = !DILocation(line: 146, column: 11, scope: !172)
!174 = !DILocation(line: 146, column: 6, scope: !15)
!175 = !DILocation(line: 147, column: 21, scope: !176)
!176 = distinct !DILexicalBlock(scope: !172, file: !1, line: 146, column: 20)
!177 = !DILocation(line: 147, column: 3, scope: !176)
!178 = !DILocation(line: 148, column: 3, scope: !176)
!179 = !DILocation(line: 151, column: 2, scope: !15)
!180 = !DILocation(line: 151, column: 5, scope: !15)
!181 = !DILocation(line: 151, column: 10, scope: !15)
!182 = !DILocation(line: 152, column: 2, scope: !15)
!183 = !DILocation(line: 152, column: 5, scope: !15)
!184 = !DILocation(line: 152, column: 10, scope: !15)
!185 = !DILocation(line: 153, column: 12, scope: !15)
!186 = !DILocation(line: 153, column: 2, scope: !15)
!187 = !DILocation(line: 153, column: 5, scope: !15)
!188 = !DILocation(line: 153, column: 10, scope: !15)
!189 = !DILocation(line: 154, column: 2, scope: !15)
!190 = !DILocation(line: 154, column: 5, scope: !15)
!191 = !DILocation(line: 154, column: 10, scope: !15)
!192 = !DILocation(line: 155, column: 2, scope: !15)
!193 = !DILocation(line: 155, column: 5, scope: !15)
!194 = !DILocation(line: 155, column: 13, scope: !15)
!195 = !DILocation(line: 156, column: 2, scope: !15)
!196 = !DILocation(line: 156, column: 5, scope: !15)
!197 = !DILocation(line: 156, column: 11, scope: !15)
!198 = !DILocation(line: 157, column: 2, scope: !15)
!199 = !DILocation(line: 157, column: 5, scope: !15)
!200 = !DILocation(line: 157, column: 11, scope: !15)
!201 = !DILocation(line: 158, column: 2, scope: !15)
!202 = !DILocation(line: 158, column: 5, scope: !15)
!203 = !DILocation(line: 158, column: 10, scope: !15)
!204 = !DILocation(line: 176, column: 16, scope: !15)
!205 = !DILocation(line: 176, column: 2, scope: !15)
!206 = !DILocation(line: 176, column: 8, scope: !15)
!207 = !DILocation(line: 176, column: 14, scope: !15)
!208 = !DILocation(line: 177, column: 6, scope: !209)
!209 = distinct !DILexicalBlock(scope: !15, file: !1, line: 177, column: 6)
!210 = !DILocation(line: 177, column: 12, scope: !209)
!211 = !DILocation(line: 177, column: 18, scope: !209)
!212 = !DILocation(line: 177, column: 6, scope: !15)
!213 = !DILocation(line: 178, column: 8, scope: !214)
!214 = distinct !DILexicalBlock(scope: !209, file: !1, line: 177, column: 27)
!215 = !DILocation(line: 178, column: 3, scope: !214)
!216 = !DILocation(line: 179, column: 21, scope: !214)
!217 = !DILocation(line: 179, column: 3, scope: !214)
!218 = !DILocation(line: 180, column: 3, scope: !214)
!219 = !DILocation(line: 182, column: 2, scope: !15)
!220 = !DILocation(line: 182, column: 8, scope: !15)
!221 = !DILocation(line: 182, column: 26, scope: !15)
!222 = !DILocation(line: 185, column: 20, scope: !15)
!223 = !DILocation(line: 185, column: 2, scope: !15)
!224 = !DILocation(line: 187, column: 2, scope: !15)
!225 = !DILocation(line: 189, column: 1, scope: !15)
!226 = !DILocalVariable(name: "f", arg: 1, scope: !143, file: !1, line: 450, type: !119)
!227 = !DILocation(line: 450, column: 54, scope: !143)
!228 = !DILocalVariable(name: "data", scope: !143, file: !1, line: 452, type: !5)
!229 = !DILocation(line: 452, column: 21, scope: !143)
!230 = !DILocation(line: 452, column: 49, scope: !143)
!231 = !DILocation(line: 452, column: 52, scope: !143)
!232 = !DILocation(line: 452, column: 28, scope: !143)
!233 = !DILocalVariable(name: "as", scope: !143, file: !1, line: 453, type: !97)
!234 = !DILocation(line: 453, column: 24, scope: !143)
!235 = !DILocalVariable(name: "r", scope: !143, file: !1, line: 454, type: !9)
!236 = !DILocation(line: 454, column: 6, scope: !143)
!237 = !DILocation(line: 456, column: 2, scope: !143)
!238 = !DILocation(line: 456, column: 2, scope: !239)
!239 = !DILexicalBlockFile(scope: !240, file: !1, discriminator: 1)
!240 = distinct !DILexicalBlock(scope: !143, file: !1, line: 456, column: 2)
!241 = !DILocation(line: 457, column: 2, scope: !143)
!242 = !DILocation(line: 459, column: 6, scope: !243)
!243 = distinct !DILexicalBlock(scope: !143, file: !1, line: 459, column: 6)
!244 = !DILocation(line: 459, column: 12, scope: !243)
!245 = !DILocation(line: 459, column: 30, scope: !243)
!246 = !DILocation(line: 459, column: 6, scope: !143)
!247 = !DILocation(line: 460, column: 3, scope: !248)
!248 = distinct !DILexicalBlock(scope: !243, file: !1, line: 459, column: 35)
!249 = !DILocation(line: 461, column: 3, scope: !248)
!250 = !DILocation(line: 462, column: 37, scope: !248)
!251 = !DILocation(line: 462, column: 43, scope: !248)
!252 = !DILocation(line: 462, column: 35, scope: !248)
!253 = !DILocation(line: 462, column: 31, scope: !248)
!254 = !DILocation(line: 462, column: 3, scope: !248)
!255 = !DILocation(line: 463, column: 2, scope: !248)
!256 = !DILocation(line: 465, column: 35, scope: !143)
!257 = !DILocation(line: 465, column: 38, scope: !143)
!258 = !DILocation(line: 465, column: 44, scope: !143)
!259 = !DILocation(line: 465, column: 54, scope: !143)
!260 = !DILocation(line: 465, column: 6, scope: !143)
!261 = !DILocation(line: 465, column: 4, scope: !143)
!262 = !DILocation(line: 466, column: 2, scope: !143)
!263 = !DILocation(line: 467, column: 10, scope: !143)
!264 = !DILocation(line: 467, column: 2, scope: !143)
!265 = !DILocalVariable(name: "f", arg: 1, scope: !142, file: !1, line: 208, type: !119)
!266 = !DILocation(line: 208, column: 57, scope: !142)
!267 = !DILocalVariable(name: "key", arg: 2, scope: !142, file: !1, line: 208, type: !86)
!268 = !DILocation(line: 208, column: 72, scope: !142)
!269 = !DILocalVariable(name: "value", arg: 3, scope: !142, file: !1, line: 209, type: !86)
!270 = !DILocation(line: 209, column: 17, scope: !142)
!271 = !DILocalVariable(name: "data", scope: !142, file: !1, line: 211, type: !5)
!272 = !DILocation(line: 211, column: 21, scope: !142)
!273 = !DILocation(line: 211, column: 49, scope: !142)
!274 = !DILocation(line: 211, column: 52, scope: !142)
!275 = !DILocation(line: 211, column: 28, scope: !142)
!276 = !DILocation(line: 213, column: 13, scope: !277)
!277 = distinct !DILexicalBlock(scope: !142, file: !1, line: 213, column: 6)
!278 = !DILocation(line: 213, column: 6, scope: !277)
!279 = !DILocation(line: 213, column: 39, scope: !277)
!280 = !DILocation(line: 213, column: 6, scope: !142)
!281 = !DILocation(line: 214, column: 7, scope: !282)
!282 = distinct !DILexicalBlock(scope: !283, file: !1, line: 214, column: 7)
!283 = distinct !DILexicalBlock(scope: !277, file: !1, line: 213, column: 45)
!284 = !DILocation(line: 214, column: 13, scope: !282)
!285 = !DILocation(line: 214, column: 21, scope: !282)
!286 = !DILocation(line: 214, column: 26, scope: !287)
!287 = !DILexicalBlockFile(scope: !282, file: !1, discriminator: 1)
!288 = !DILocation(line: 214, column: 35, scope: !287)
!289 = !DILocation(line: 214, column: 42, scope: !287)
!290 = !DILocation(line: 214, column: 45, scope: !291)
!291 = !DILexicalBlockFile(scope: !282, file: !1, discriminator: 2)
!292 = !DILocation(line: 214, column: 54, scope: !291)
!293 = !DILocation(line: 214, column: 62, scope: !291)
!294 = !DILocation(line: 215, column: 7, scope: !282)
!295 = !DILocation(line: 215, column: 16, scope: !282)
!296 = !DILocation(line: 214, column: 7, scope: !297)
!297 = !DILexicalBlockFile(scope: !283, file: !1, discriminator: 3)
!298 = !DILocation(line: 216, column: 4, scope: !282)
!299 = !DILocation(line: 217, column: 29, scope: !283)
!300 = !DILocation(line: 217, column: 38, scope: !283)
!301 = !DILocation(line: 217, column: 3, scope: !283)
!302 = !DILocation(line: 217, column: 9, scope: !283)
!303 = !DILocation(line: 217, column: 27, scope: !283)
!304 = !DILocation(line: 218, column: 3, scope: !283)
!305 = !DILocation(line: 223, column: 2, scope: !142)
!306 = !DILocation(line: 224, column: 1, scope: !142)
!307 = !DILocalVariable(name: "f", arg: 1, scope: !144, file: !1, line: 471, type: !119)
!308 = !DILocation(line: 471, column: 55, scope: !144)
!309 = !DILocalVariable(name: "buff", arg: 2, scope: !144, file: !1, line: 472, type: !49)
!310 = !DILocation(line: 472, column: 17, scope: !144)
!311 = !DILocalVariable(name: "length", arg: 3, scope: !144, file: !1, line: 472, type: !51)
!312 = !DILocation(line: 472, column: 30, scope: !144)
!313 = !DILocalVariable(name: "data", scope: !144, file: !1, line: 474, type: !5)
!314 = !DILocation(line: 474, column: 21, scope: !144)
!315 = !DILocation(line: 474, column: 49, scope: !144)
!316 = !DILocation(line: 474, column: 52, scope: !144)
!317 = !DILocation(line: 474, column: 28, scope: !144)
!318 = !DILocation(line: 476, column: 39, scope: !144)
!319 = !DILocation(line: 476, column: 42, scope: !144)
!320 = !DILocation(line: 476, column: 48, scope: !144)
!321 = !DILocation(line: 476, column: 55, scope: !144)
!322 = !DILocation(line: 476, column: 61, scope: !144)
!323 = !DILocation(line: 476, column: 9, scope: !144)
!324 = !DILocation(line: 476, column: 2, scope: !144)
!325 = !DILocalVariable(name: "f", arg: 1, scope: !145, file: !1, line: 480, type: !119)
!326 = !DILocation(line: 480, column: 55, scope: !145)
!327 = !DILocalVariable(name: "data", scope: !145, file: !1, line: 482, type: !5)
!328 = !DILocation(line: 482, column: 21, scope: !145)
!329 = !DILocation(line: 482, column: 49, scope: !145)
!330 = !DILocation(line: 482, column: 52, scope: !145)
!331 = !DILocation(line: 482, column: 28, scope: !145)
!332 = !DILocation(line: 484, column: 39, scope: !145)
!333 = !DILocation(line: 484, column: 42, scope: !145)
!334 = !DILocation(line: 484, column: 48, scope: !145)
!335 = !DILocation(line: 484, column: 9, scope: !145)
!336 = !DILocation(line: 484, column: 2, scope: !145)
!337 = !DILocalVariable(name: "f", arg: 1, scope: !116, file: !1, line: 192, type: !119)
!338 = !DILocation(line: 192, column: 54, scope: !116)
!339 = !DILocalVariable(name: "data", scope: !116, file: !1, line: 194, type: !5)
!340 = !DILocation(line: 194, column: 21, scope: !116)
!341 = !DILocation(line: 194, column: 49, scope: !116)
!342 = !DILocation(line: 194, column: 52, scope: !116)
!343 = !DILocation(line: 194, column: 28, scope: !116)
!344 = !DILocation(line: 201, column: 31, scope: !116)
!345 = !DILocation(line: 201, column: 37, scope: !116)
!346 = !DILocation(line: 201, column: 2, scope: !116)
!347 = !DILocation(line: 203, column: 7, scope: !116)
!348 = !DILocation(line: 203, column: 2, scope: !116)
!349 = !DILocation(line: 204, column: 2, scope: !116)
