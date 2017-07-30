; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_virtual.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.archive = type { i32, i32, %struct.archive_vtable*, i32, i8*, i32, i8*, i32, i32, i8*, %struct.archive_string, i8*, i32, i32, %struct.archive_string_conv*, i8*, i64, i64, i64, i8, i64 }
%struct.archive_vtable = type { i32 (%struct.archive*)*, i32 (%struct.archive*)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*)*, i64 (%struct.archive*, i8*, i64)*, i64 (%struct.archive*, i8*, i64, i64)*, i32 (%struct.archive*, %struct.archive_entry**)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*, i8**, i64*, i64*)*, i32 (%struct.archive*)*, i64 (%struct.archive*, i32)*, {}*, i8* (%struct.archive*, i32)* }
%struct.archive_entry = type opaque
%struct.archive_string = type { i8*, i64, i64 }
%struct.archive_string_conv = type opaque

@.str = private unnamed_addr constant [39 x i8] c"archive_write_data_block not supported\00", align 1

; Function Attrs: nounwind uwtable
define i32 @archive_filter_code(%struct.archive* %a, i32 %n) #0 !dbg !6 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  %n.addr = alloca i32, align 4
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !137, metadata !138), !dbg !139
  store i32 %n, i32* %n.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %n.addr, metadata !140, metadata !138), !dbg !141
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !142
  %vtable = getelementptr inbounds %struct.archive, %struct.archive* %0, i32 0, i32 2, !dbg !143
  %1 = load %struct.archive_vtable*, %struct.archive_vtable** %vtable, align 8, !dbg !143
  %archive_filter_code = getelementptr inbounds %struct.archive_vtable, %struct.archive_vtable* %1, i32 0, i32 11, !dbg !144
  %archive_filter_code1 = bitcast {}** %archive_filter_code to i32 (%struct.archive*, i32)**, !dbg !144
  %2 = load i32 (%struct.archive*, i32)*, i32 (%struct.archive*, i32)** %archive_filter_code1, align 8, !dbg !144
  %3 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !145
  %4 = load i32, i32* %n.addr, align 4, !dbg !146
  %call = call i32 %2(%struct.archive* %3, i32 %4), !dbg !147
  ret i32 %call, !dbg !148
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define i32 @archive_filter_count(%struct.archive* %a) #0 !dbg !108 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !149, metadata !138), !dbg !150
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !151
  %vtable = getelementptr inbounds %struct.archive, %struct.archive* %0, i32 0, i32 2, !dbg !152
  %1 = load %struct.archive_vtable*, %struct.archive_vtable** %vtable, align 8, !dbg !152
  %archive_filter_count = getelementptr inbounds %struct.archive_vtable, %struct.archive_vtable* %1, i32 0, i32 9, !dbg !153
  %2 = load i32 (%struct.archive*)*, i32 (%struct.archive*)** %archive_filter_count, align 8, !dbg !153
  %3 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !154
  %call = call i32 %2(%struct.archive* %3), !dbg !155
  ret i32 %call, !dbg !156
}

; Function Attrs: nounwind uwtable
define i8* @archive_filter_name(%struct.archive* %a, i32 %n) #0 !dbg !109 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  %n.addr = alloca i32, align 4
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !157, metadata !138), !dbg !158
  store i32 %n, i32* %n.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %n.addr, metadata !159, metadata !138), !dbg !160
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !161
  %vtable = getelementptr inbounds %struct.archive, %struct.archive* %0, i32 0, i32 2, !dbg !162
  %1 = load %struct.archive_vtable*, %struct.archive_vtable** %vtable, align 8, !dbg !162
  %archive_filter_name = getelementptr inbounds %struct.archive_vtable, %struct.archive_vtable* %1, i32 0, i32 12, !dbg !163
  %2 = load i8* (%struct.archive*, i32)*, i8* (%struct.archive*, i32)** %archive_filter_name, align 8, !dbg !163
  %3 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !164
  %4 = load i32, i32* %n.addr, align 4, !dbg !165
  %call = call i8* %2(%struct.archive* %3, i32 %4), !dbg !166
  ret i8* %call, !dbg !167
}

; Function Attrs: nounwind uwtable
define i64 @archive_filter_bytes(%struct.archive* %a, i32 %n) #0 !dbg !110 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  %n.addr = alloca i32, align 4
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !168, metadata !138), !dbg !169
  store i32 %n, i32* %n.addr, align 4
  call void @llvm.dbg.declare(metadata i32* %n.addr, metadata !170, metadata !138), !dbg !171
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !172
  %vtable = getelementptr inbounds %struct.archive, %struct.archive* %0, i32 0, i32 2, !dbg !173
  %1 = load %struct.archive_vtable*, %struct.archive_vtable** %vtable, align 8, !dbg !173
  %archive_filter_bytes = getelementptr inbounds %struct.archive_vtable, %struct.archive_vtable* %1, i32 0, i32 10, !dbg !174
  %2 = load i64 (%struct.archive*, i32)*, i64 (%struct.archive*, i32)** %archive_filter_bytes, align 8, !dbg !174
  %3 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !175
  %4 = load i32, i32* %n.addr, align 4, !dbg !176
  %call = call i64 %2(%struct.archive* %3, i32 %4), !dbg !177
  ret i64 %call, !dbg !178
}

; Function Attrs: nounwind uwtable
define i32 @archive_free(%struct.archive* %a) #0 !dbg !114 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !179, metadata !138), !dbg !180
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !181
  %cmp = icmp eq %struct.archive* %0, null, !dbg !183
  br i1 %cmp, label %if.then, label %if.end, !dbg !184

if.then:                                          ; preds = %entry
  store i32 0, i32* %retval, align 4, !dbg !185
  br label %return, !dbg !185

if.end:                                           ; preds = %entry
  %1 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !186
  %vtable = getelementptr inbounds %struct.archive, %struct.archive* %1, i32 0, i32 2, !dbg !187
  %2 = load %struct.archive_vtable*, %struct.archive_vtable** %vtable, align 8, !dbg !187
  %archive_free = getelementptr inbounds %struct.archive_vtable, %struct.archive_vtable* %2, i32 0, i32 1, !dbg !188
  %3 = load i32 (%struct.archive*)*, i32 (%struct.archive*)** %archive_free, align 8, !dbg !188
  %4 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !189
  %call = call i32 %3(%struct.archive* %4), !dbg !190
  store i32 %call, i32* %retval, align 4, !dbg !191
  br label %return, !dbg !191

return:                                           ; preds = %if.end, %if.then
  %5 = load i32, i32* %retval, align 4, !dbg !192
  ret i32 %5, !dbg !192
}

; Function Attrs: nounwind uwtable
define i32 @archive_write_close(%struct.archive* %a) #0 !dbg !115 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !193, metadata !138), !dbg !194
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !195
  %vtable = getelementptr inbounds %struct.archive, %struct.archive* %0, i32 0, i32 2, !dbg !196
  %1 = load %struct.archive_vtable*, %struct.archive_vtable** %vtable, align 8, !dbg !196
  %archive_close = getelementptr inbounds %struct.archive_vtable, %struct.archive_vtable* %1, i32 0, i32 0, !dbg !197
  %2 = load i32 (%struct.archive*)*, i32 (%struct.archive*)** %archive_close, align 8, !dbg !197
  %3 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !198
  %call = call i32 %2(%struct.archive* %3), !dbg !199
  ret i32 %call, !dbg !200
}

; Function Attrs: nounwind uwtable
define i32 @archive_read_close(%struct.archive* %a) #0 !dbg !116 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !201, metadata !138), !dbg !202
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !203
  %vtable = getelementptr inbounds %struct.archive, %struct.archive* %0, i32 0, i32 2, !dbg !204
  %1 = load %struct.archive_vtable*, %struct.archive_vtable** %vtable, align 8, !dbg !204
  %archive_close = getelementptr inbounds %struct.archive_vtable, %struct.archive_vtable* %1, i32 0, i32 0, !dbg !205
  %2 = load i32 (%struct.archive*)*, i32 (%struct.archive*)** %archive_close, align 8, !dbg !205
  %3 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !206
  %call = call i32 %2(%struct.archive* %3), !dbg !207
  ret i32 %call, !dbg !208
}

; Function Attrs: nounwind uwtable
define i32 @archive_write_fail(%struct.archive* %a) #0 !dbg !117 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !209, metadata !138), !dbg !210
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !211
  %state = getelementptr inbounds %struct.archive, %struct.archive* %0, i32 0, i32 1, !dbg !212
  store i32 32768, i32* %state, align 4, !dbg !213
  %1 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !214
  %state1 = getelementptr inbounds %struct.archive, %struct.archive* %1, i32 0, i32 1, !dbg !215
  %2 = load i32, i32* %state1, align 4, !dbg !215
  ret i32 %2, !dbg !216
}

; Function Attrs: nounwind uwtable
define i32 @archive_write_free(%struct.archive* %a) #0 !dbg !118 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !217, metadata !138), !dbg !218
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !219
  %call = call i32 @archive_free(%struct.archive* %0), !dbg !220
  ret i32 %call, !dbg !221
}

; Function Attrs: nounwind uwtable
define i32 @archive_write_finish(%struct.archive* %a) #0 !dbg !119 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !222, metadata !138), !dbg !223
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !224
  %call = call i32 @archive_write_free(%struct.archive* %0), !dbg !225
  ret i32 %call, !dbg !226
}

; Function Attrs: nounwind uwtable
define i32 @archive_read_free(%struct.archive* %a) #0 !dbg !120 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !227, metadata !138), !dbg !228
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !229
  %call = call i32 @archive_free(%struct.archive* %0), !dbg !230
  ret i32 %call, !dbg !231
}

; Function Attrs: nounwind uwtable
define i32 @archive_read_finish(%struct.archive* %a) #0 !dbg !121 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !232, metadata !138), !dbg !233
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !234
  %call = call i32 @archive_read_free(%struct.archive* %0), !dbg !235
  ret i32 %call, !dbg !236
}

; Function Attrs: nounwind uwtable
define i32 @archive_write_header(%struct.archive* %a, %struct.archive_entry* %entry1) #0 !dbg !122 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !237, metadata !138), !dbg !238
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !239, metadata !138), !dbg !240
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !241
  %file_count = getelementptr inbounds %struct.archive, %struct.archive* %0, i32 0, i32 7, !dbg !242
  %1 = load i32, i32* %file_count, align 8, !dbg !243
  %inc = add nsw i32 %1, 1, !dbg !243
  store i32 %inc, i32* %file_count, align 8, !dbg !243
  %2 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !244
  %vtable = getelementptr inbounds %struct.archive, %struct.archive* %2, i32 0, i32 2, !dbg !245
  %3 = load %struct.archive_vtable*, %struct.archive_vtable** %vtable, align 8, !dbg !245
  %archive_write_header = getelementptr inbounds %struct.archive_vtable, %struct.archive_vtable* %3, i32 0, i32 2, !dbg !246
  %4 = load i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*, %struct.archive_entry*)** %archive_write_header, align 8, !dbg !246
  %5 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !247
  %6 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !248
  %call = call i32 %4(%struct.archive* %5, %struct.archive_entry* %6), !dbg !249
  ret i32 %call, !dbg !250
}

; Function Attrs: nounwind uwtable
define i32 @archive_write_finish_entry(%struct.archive* %a) #0 !dbg !123 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !251, metadata !138), !dbg !252
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !253
  %vtable = getelementptr inbounds %struct.archive, %struct.archive* %0, i32 0, i32 2, !dbg !254
  %1 = load %struct.archive_vtable*, %struct.archive_vtable** %vtable, align 8, !dbg !254
  %archive_write_finish_entry = getelementptr inbounds %struct.archive_vtable, %struct.archive_vtable* %1, i32 0, i32 3, !dbg !255
  %2 = load i32 (%struct.archive*)*, i32 (%struct.archive*)** %archive_write_finish_entry, align 8, !dbg !255
  %3 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !256
  %call = call i32 %2(%struct.archive* %3), !dbg !257
  ret i32 %call, !dbg !258
}

; Function Attrs: nounwind uwtable
define i64 @archive_write_data(%struct.archive* %a, i8* %buff, i64 %s) #0 !dbg !124 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  %buff.addr = alloca i8*, align 8
  %s.addr = alloca i64, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !259, metadata !138), !dbg !260
  store i8* %buff, i8** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buff.addr, metadata !261, metadata !138), !dbg !262
  store i64 %s, i64* %s.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %s.addr, metadata !263, metadata !138), !dbg !264
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !265
  %vtable = getelementptr inbounds %struct.archive, %struct.archive* %0, i32 0, i32 2, !dbg !266
  %1 = load %struct.archive_vtable*, %struct.archive_vtable** %vtable, align 8, !dbg !266
  %archive_write_data = getelementptr inbounds %struct.archive_vtable, %struct.archive_vtable* %1, i32 0, i32 4, !dbg !267
  %2 = load i64 (%struct.archive*, i8*, i64)*, i64 (%struct.archive*, i8*, i64)** %archive_write_data, align 8, !dbg !267
  %3 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !268
  %4 = load i8*, i8** %buff.addr, align 8, !dbg !269
  %5 = load i64, i64* %s.addr, align 8, !dbg !270
  %call = call i64 %2(%struct.archive* %3, i8* %4, i64 %5), !dbg !271
  ret i64 %call, !dbg !272
}

; Function Attrs: nounwind uwtable
define i64 @archive_write_data_block(%struct.archive* %a, i8* %buff, i64 %s, i64 %o) #0 !dbg !128 {
entry:
  %retval = alloca i64, align 8
  %a.addr = alloca %struct.archive*, align 8
  %buff.addr = alloca i8*, align 8
  %s.addr = alloca i64, align 8
  %o.addr = alloca i64, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !273, metadata !138), !dbg !274
  store i8* %buff, i8** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %buff.addr, metadata !275, metadata !138), !dbg !276
  store i64 %s, i64* %s.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %s.addr, metadata !277, metadata !138), !dbg !278
  store i64 %o, i64* %o.addr, align 8
  call void @llvm.dbg.declare(metadata i64* %o.addr, metadata !279, metadata !138), !dbg !280
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !281
  %vtable = getelementptr inbounds %struct.archive, %struct.archive* %0, i32 0, i32 2, !dbg !283
  %1 = load %struct.archive_vtable*, %struct.archive_vtable** %vtable, align 8, !dbg !283
  %archive_write_data_block = getelementptr inbounds %struct.archive_vtable, %struct.archive_vtable* %1, i32 0, i32 5, !dbg !284
  %2 = load i64 (%struct.archive*, i8*, i64, i64)*, i64 (%struct.archive*, i8*, i64, i64)** %archive_write_data_block, align 8, !dbg !284
  %cmp = icmp eq i64 (%struct.archive*, i8*, i64, i64)* %2, null, !dbg !285
  br i1 %cmp, label %if.then, label %if.end, !dbg !286

if.then:                                          ; preds = %entry
  %3 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !287
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %3, i32 -1, i8* getelementptr inbounds ([39 x i8], [39 x i8]* @.str, i32 0, i32 0)), !dbg !289
  %4 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !290
  %state = getelementptr inbounds %struct.archive, %struct.archive* %4, i32 0, i32 1, !dbg !291
  store i32 32768, i32* %state, align 4, !dbg !292
  store i64 -30, i64* %retval, align 8, !dbg !293
  br label %return, !dbg !293

if.end:                                           ; preds = %entry
  %5 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !294
  %vtable1 = getelementptr inbounds %struct.archive, %struct.archive* %5, i32 0, i32 2, !dbg !295
  %6 = load %struct.archive_vtable*, %struct.archive_vtable** %vtable1, align 8, !dbg !295
  %archive_write_data_block2 = getelementptr inbounds %struct.archive_vtable, %struct.archive_vtable* %6, i32 0, i32 5, !dbg !296
  %7 = load i64 (%struct.archive*, i8*, i64, i64)*, i64 (%struct.archive*, i8*, i64, i64)** %archive_write_data_block2, align 8, !dbg !296
  %8 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !297
  %9 = load i8*, i8** %buff.addr, align 8, !dbg !298
  %10 = load i64, i64* %s.addr, align 8, !dbg !299
  %11 = load i64, i64* %o.addr, align 8, !dbg !300
  %call = call i64 %7(%struct.archive* %8, i8* %9, i64 %10, i64 %11), !dbg !301
  store i64 %call, i64* %retval, align 8, !dbg !302
  br label %return, !dbg !302

return:                                           ; preds = %if.end, %if.then
  %12 = load i64, i64* %retval, align 8, !dbg !303
  ret i64 %12, !dbg !303
}

declare void @archive_set_error(%struct.archive*, i32, i8*, ...) #2

; Function Attrs: nounwind uwtable
define i32 @archive_read_next_header(%struct.archive* %a, %struct.archive_entry** %entry1) #0 !dbg !131 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  %entry.addr = alloca %struct.archive_entry**, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !304, metadata !138), !dbg !305
  store %struct.archive_entry** %entry1, %struct.archive_entry*** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry*** %entry.addr, metadata !306, metadata !138), !dbg !307
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !308
  %vtable = getelementptr inbounds %struct.archive, %struct.archive* %0, i32 0, i32 2, !dbg !309
  %1 = load %struct.archive_vtable*, %struct.archive_vtable** %vtable, align 8, !dbg !309
  %archive_read_next_header = getelementptr inbounds %struct.archive_vtable, %struct.archive_vtable* %1, i32 0, i32 6, !dbg !310
  %2 = load i32 (%struct.archive*, %struct.archive_entry**)*, i32 (%struct.archive*, %struct.archive_entry**)** %archive_read_next_header, align 8, !dbg !310
  %3 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !311
  %4 = load %struct.archive_entry**, %struct.archive_entry*** %entry.addr, align 8, !dbg !312
  %call = call i32 %2(%struct.archive* %3, %struct.archive_entry** %4), !dbg !313
  ret i32 %call, !dbg !314
}

; Function Attrs: nounwind uwtable
define i32 @archive_read_next_header2(%struct.archive* %a, %struct.archive_entry* %entry1) #0 !dbg !132 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  %entry.addr = alloca %struct.archive_entry*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !315, metadata !138), !dbg !316
  store %struct.archive_entry* %entry1, %struct.archive_entry** %entry.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive_entry** %entry.addr, metadata !317, metadata !138), !dbg !318
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !319
  %vtable = getelementptr inbounds %struct.archive, %struct.archive* %0, i32 0, i32 2, !dbg !320
  %1 = load %struct.archive_vtable*, %struct.archive_vtable** %vtable, align 8, !dbg !320
  %archive_read_next_header2 = getelementptr inbounds %struct.archive_vtable, %struct.archive_vtable* %1, i32 0, i32 7, !dbg !321
  %2 = load i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*, %struct.archive_entry*)** %archive_read_next_header2, align 8, !dbg !321
  %3 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !322
  %4 = load %struct.archive_entry*, %struct.archive_entry** %entry.addr, align 8, !dbg !323
  %call = call i32 %2(%struct.archive* %3, %struct.archive_entry* %4), !dbg !324
  ret i32 %call, !dbg !325
}

; Function Attrs: nounwind uwtable
define i32 @archive_read_data_block(%struct.archive* %a, i8** %buff, i64* %s, i64* %o) #0 !dbg !133 {
entry:
  %a.addr = alloca %struct.archive*, align 8
  %buff.addr = alloca i8**, align 8
  %s.addr = alloca i64*, align 8
  %o.addr = alloca i64*, align 8
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !326, metadata !138), !dbg !327
  store i8** %buff, i8*** %buff.addr, align 8
  call void @llvm.dbg.declare(metadata i8*** %buff.addr, metadata !328, metadata !138), !dbg !329
  store i64* %s, i64** %s.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %s.addr, metadata !330, metadata !138), !dbg !331
  store i64* %o, i64** %o.addr, align 8
  call void @llvm.dbg.declare(metadata i64** %o.addr, metadata !332, metadata !138), !dbg !333
  %0 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !334
  %vtable = getelementptr inbounds %struct.archive, %struct.archive* %0, i32 0, i32 2, !dbg !335
  %1 = load %struct.archive_vtable*, %struct.archive_vtable** %vtable, align 8, !dbg !335
  %archive_read_data_block = getelementptr inbounds %struct.archive_vtable, %struct.archive_vtable* %1, i32 0, i32 8, !dbg !336
  %2 = load i32 (%struct.archive*, i8**, i64*, i64*)*, i32 (%struct.archive*, i8**, i64*, i64*)** %archive_read_data_block, align 8, !dbg !336
  %3 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !337
  %4 = load i8**, i8*** %buff.addr, align 8, !dbg !338
  %5 = load i64*, i64** %s.addr, align 8, !dbg !339
  %6 = load i64*, i64** %o.addr, align 8, !dbg !340
  %call = call i32 %2(%struct.archive* %3, i8** %4, i64* %5, i64* %6), !dbg !341
  ret i32 %call, !dbg !342
}

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!134, !135}
!llvm.ident = !{!136}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !5)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_virtual.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4}
!4 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!5 = !{!6, !108, !109, !110, !114, !115, !116, !117, !118, !119, !120, !121, !122, !123, !124, !128, !131, !132, !133}
!6 = distinct !DISubprogram(name: "archive_filter_code", scope: !1, file: !1, line: 34, type: !7, isLocal: false, isDefinition: true, scopeLine: 35, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!7 = !DISubroutineType(types: !8)
!8 = !{!9, !10, !9}
!9 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!10 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !11, size: 64, align: 64)
!11 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive", file: !12, line: 89, size: 1280, align: 64, elements: !13)
!12 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!13 = !{!14, !16, !17, !81, !82, !83, !84, !85, !86, !87, !88, !96, !97, !98, !99, !102, !103, !104, !105, !106, !107}
!14 = !DIDerivedType(tag: DW_TAG_member, name: "magic", scope: !11, file: !12, line: 96, baseType: !15, size: 32, align: 32)
!15 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!16 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !11, file: !12, line: 97, baseType: !15, size: 32, align: 32, offset: 32)
!17 = !DIDerivedType(tag: DW_TAG_member, name: "vtable", scope: !11, file: !12, line: 103, baseType: !18, size: 64, align: 64, offset: 64)
!18 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !19, size: 64, align: 64)
!19 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_vtable", file: !12, line: 63, size: 832, align: 64, elements: !20)
!20 = !{!21, !25, !26, !33, !34, !48, !54, !59, !60, !67, !68, !72, !74}
!21 = !DIDerivedType(tag: DW_TAG_member, name: "archive_close", scope: !19, file: !12, line: 64, baseType: !22, size: 64, align: 64)
!22 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !23, size: 64, align: 64)
!23 = !DISubroutineType(types: !24)
!24 = !{!9, !10}
!25 = !DIDerivedType(tag: DW_TAG_member, name: "archive_free", scope: !19, file: !12, line: 65, baseType: !22, size: 64, align: 64, offset: 64)
!26 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_header", scope: !19, file: !12, line: 66, baseType: !27, size: 64, align: 64, offset: 128)
!27 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !28, size: 64, align: 64)
!28 = !DISubroutineType(types: !29)
!29 = !{!9, !10, !30}
!30 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !31, size: 64, align: 64)
!31 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_entry", file: !32, line: 180, flags: DIFlagFwdDecl)
!32 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!33 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_finish_entry", scope: !19, file: !12, line: 68, baseType: !22, size: 64, align: 64, offset: 192)
!34 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data", scope: !19, file: !12, line: 69, baseType: !35, size: 64, align: 64, offset: 256)
!35 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !36, size: 64, align: 64)
!36 = !DISubroutineType(types: !37)
!37 = !{!38, !10, !43, !45}
!38 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !39, line: 102, baseType: !40)
!39 = !DIFile(filename: "/usr/include/stdio.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!40 = !DIDerivedType(tag: DW_TAG_typedef, name: "__ssize_t", file: !41, line: 172, baseType: !42)
!41 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/bits/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!42 = !DIBasicType(name: "long int", size: 64, align: 64, encoding: DW_ATE_signed)
!43 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !44, size: 64, align: 64)
!44 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!45 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !46, line: 62, baseType: !47)
!46 = !DIFile(filename: "/opt/llvm-build/bin/../lib/clang/3.8.0/include/stddef.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!47 = !DIBasicType(name: "long unsigned int", size: 64, align: 64, encoding: DW_ATE_unsigned)
!48 = !DIDerivedType(tag: DW_TAG_member, name: "archive_write_data_block", scope: !19, file: !12, line: 71, baseType: !49, size: 64, align: 64, offset: 320)
!49 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !50, size: 64, align: 64)
!50 = !DISubroutineType(types: !51)
!51 = !{!38, !10, !43, !45, !52}
!52 = !DIDerivedType(tag: DW_TAG_typedef, name: "int64_t", file: !53, line: 40, baseType: !42)
!53 = !DIFile(filename: "/usr/include/stdint.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!54 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header", scope: !19, file: !12, line: 74, baseType: !55, size: 64, align: 64, offset: 384)
!55 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !56, size: 64, align: 64)
!56 = !DISubroutineType(types: !57)
!57 = !{!9, !10, !58}
!58 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !30, size: 64, align: 64)
!59 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_next_header2", scope: !19, file: !12, line: 76, baseType: !27, size: 64, align: 64, offset: 448)
!60 = !DIDerivedType(tag: DW_TAG_member, name: "archive_read_data_block", scope: !19, file: !12, line: 78, baseType: !61, size: 64, align: 64, offset: 512)
!61 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !62, size: 64, align: 64)
!62 = !DISubroutineType(types: !63)
!63 = !{!9, !10, !64, !65, !66}
!64 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !43, size: 64, align: 64)
!65 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !45, size: 64, align: 64)
!66 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !52, size: 64, align: 64)
!67 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_count", scope: !19, file: !12, line: 81, baseType: !22, size: 64, align: 64, offset: 576)
!68 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_bytes", scope: !19, file: !12, line: 82, baseType: !69, size: 64, align: 64, offset: 640)
!69 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !70, size: 64, align: 64)
!70 = !DISubroutineType(types: !71)
!71 = !{!52, !10, !9}
!72 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_code", scope: !19, file: !12, line: 83, baseType: !73, size: 64, align: 64, offset: 704)
!73 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !7, size: 64, align: 64)
!74 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_name", scope: !19, file: !12, line: 84, baseType: !75, size: 64, align: 64, offset: 768)
!75 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !76, size: 64, align: 64)
!76 = !DISubroutineType(types: !77)
!77 = !{!78, !10, !9}
!78 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !79, size: 64, align: 64)
!79 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !80)
!80 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!81 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format", scope: !11, file: !12, line: 105, baseType: !9, size: 32, align: 32, offset: 128)
!82 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format_name", scope: !11, file: !12, line: 106, baseType: !78, size: 64, align: 64, offset: 192)
!83 = !DIDerivedType(tag: DW_TAG_member, name: "compression_code", scope: !11, file: !12, line: 108, baseType: !9, size: 32, align: 32, offset: 256)
!84 = !DIDerivedType(tag: DW_TAG_member, name: "compression_name", scope: !11, file: !12, line: 109, baseType: !78, size: 64, align: 64, offset: 320)
!85 = !DIDerivedType(tag: DW_TAG_member, name: "file_count", scope: !11, file: !12, line: 112, baseType: !9, size: 32, align: 32, offset: 384)
!86 = !DIDerivedType(tag: DW_TAG_member, name: "archive_error_number", scope: !11, file: !12, line: 114, baseType: !9, size: 32, align: 32, offset: 416)
!87 = !DIDerivedType(tag: DW_TAG_member, name: "error", scope: !11, file: !12, line: 115, baseType: !78, size: 64, align: 64, offset: 448)
!88 = !DIDerivedType(tag: DW_TAG_member, name: "error_string", scope: !11, file: !12, line: 116, baseType: !89, size: 192, align: 64, offset: 512)
!89 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string", file: !90, line: 58, size: 192, align: 64, elements: !91)
!90 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_string.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!91 = !{!92, !94, !95}
!92 = !DIDerivedType(tag: DW_TAG_member, name: "s", scope: !89, file: !90, line: 59, baseType: !93, size: 64, align: 64)
!93 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !80, size: 64, align: 64)
!94 = !DIDerivedType(tag: DW_TAG_member, name: "length", scope: !89, file: !90, line: 60, baseType: !45, size: 64, align: 64, offset: 64)
!95 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_length", scope: !89, file: !90, line: 61, baseType: !45, size: 64, align: 64, offset: 128)
!96 = !DIDerivedType(tag: DW_TAG_member, name: "current_code", scope: !11, file: !12, line: 118, baseType: !93, size: 64, align: 64, offset: 704)
!97 = !DIDerivedType(tag: DW_TAG_member, name: "current_codepage", scope: !11, file: !12, line: 119, baseType: !15, size: 32, align: 32, offset: 768)
!98 = !DIDerivedType(tag: DW_TAG_member, name: "current_oemcp", scope: !11, file: !12, line: 120, baseType: !15, size: 32, align: 32, offset: 800)
!99 = !DIDerivedType(tag: DW_TAG_member, name: "sconv", scope: !11, file: !12, line: 121, baseType: !100, size: 64, align: 64, offset: 832)
!100 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !101, size: 64, align: 64)
!101 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string_conv", file: !90, line: 70, flags: DIFlagFwdDecl)
!102 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_block", scope: !11, file: !12, line: 127, baseType: !78, size: 64, align: 64, offset: 896)
!103 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_offset", scope: !11, file: !12, line: 128, baseType: !52, size: 64, align: 64, offset: 960)
!104 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_output_offset", scope: !11, file: !12, line: 129, baseType: !52, size: 64, align: 64, offset: 1024)
!105 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_remaining", scope: !11, file: !12, line: 130, baseType: !45, size: 64, align: 64, offset: 1088)
!106 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_is_posix_read", scope: !11, file: !12, line: 137, baseType: !80, size: 8, align: 8, offset: 1152)
!107 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_requested", scope: !11, file: !12, line: 138, baseType: !45, size: 64, align: 64, offset: 1216)
!108 = distinct !DISubprogram(name: "archive_filter_count", scope: !1, file: !1, line: 40, type: !23, isLocal: false, isDefinition: true, scopeLine: 41, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!109 = distinct !DISubprogram(name: "archive_filter_name", scope: !1, file: !1, line: 46, type: !76, isLocal: false, isDefinition: true, scopeLine: 47, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!110 = distinct !DISubprogram(name: "archive_filter_bytes", scope: !1, file: !1, line: 52, type: !111, isLocal: false, isDefinition: true, scopeLine: 53, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!111 = !DISubroutineType(types: !112)
!112 = !{!113, !10, !9}
!113 = !DIDerivedType(tag: DW_TAG_typedef, name: "la_int64_t", file: !32, line: 73, baseType: !52)
!114 = distinct !DISubprogram(name: "archive_free", scope: !1, file: !1, line: 58, type: !23, isLocal: false, isDefinition: true, scopeLine: 59, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!115 = distinct !DISubprogram(name: "archive_write_close", scope: !1, file: !1, line: 66, type: !23, isLocal: false, isDefinition: true, scopeLine: 67, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!116 = distinct !DISubprogram(name: "archive_read_close", scope: !1, file: !1, line: 72, type: !23, isLocal: false, isDefinition: true, scopeLine: 73, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!117 = distinct !DISubprogram(name: "archive_write_fail", scope: !1, file: !1, line: 78, type: !23, isLocal: false, isDefinition: true, scopeLine: 79, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!118 = distinct !DISubprogram(name: "archive_write_free", scope: !1, file: !1, line: 85, type: !23, isLocal: false, isDefinition: true, scopeLine: 86, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!119 = distinct !DISubprogram(name: "archive_write_finish", scope: !1, file: !1, line: 93, type: !23, isLocal: false, isDefinition: true, scopeLine: 94, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!120 = distinct !DISubprogram(name: "archive_read_free", scope: !1, file: !1, line: 100, type: !23, isLocal: false, isDefinition: true, scopeLine: 101, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!121 = distinct !DISubprogram(name: "archive_read_finish", scope: !1, file: !1, line: 108, type: !23, isLocal: false, isDefinition: true, scopeLine: 109, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!122 = distinct !DISubprogram(name: "archive_write_header", scope: !1, file: !1, line: 115, type: !28, isLocal: false, isDefinition: true, scopeLine: 116, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!123 = distinct !DISubprogram(name: "archive_write_finish_entry", scope: !1, file: !1, line: 122, type: !23, isLocal: false, isDefinition: true, scopeLine: 123, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!124 = distinct !DISubprogram(name: "archive_write_data", scope: !1, file: !1, line: 128, type: !125, isLocal: false, isDefinition: true, scopeLine: 129, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!125 = !DISubroutineType(types: !126)
!126 = !{!127, !10, !43, !45}
!127 = !DIDerivedType(tag: DW_TAG_typedef, name: "la_ssize_t", file: !32, line: 95, baseType: !38)
!128 = distinct !DISubprogram(name: "archive_write_data_block", scope: !1, file: !1, line: 134, type: !129, isLocal: false, isDefinition: true, scopeLine: 135, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!129 = !DISubroutineType(types: !130)
!130 = !{!127, !10, !43, !45, !52}
!131 = distinct !DISubprogram(name: "archive_read_next_header", scope: !1, file: !1, line: 146, type: !56, isLocal: false, isDefinition: true, scopeLine: 147, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!132 = distinct !DISubprogram(name: "archive_read_next_header2", scope: !1, file: !1, line: 152, type: !28, isLocal: false, isDefinition: true, scopeLine: 153, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!133 = distinct !DISubprogram(name: "archive_read_data_block", scope: !1, file: !1, line: 158, type: !62, isLocal: false, isDefinition: true, scopeLine: 160, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!134 = !{i32 2, !"Dwarf Version", i32 4}
!135 = !{i32 2, !"Debug Info Version", i32 3}
!136 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!137 = !DILocalVariable(name: "a", arg: 1, scope: !6, file: !1, line: 34, type: !10)
!138 = !DIExpression()
!139 = !DILocation(line: 34, column: 37, scope: !6)
!140 = !DILocalVariable(name: "n", arg: 2, scope: !6, file: !1, line: 34, type: !9)
!141 = !DILocation(line: 34, column: 44, scope: !6)
!142 = !DILocation(line: 36, column: 11, scope: !6)
!143 = !DILocation(line: 36, column: 14, scope: !6)
!144 = !DILocation(line: 36, column: 22, scope: !6)
!145 = !DILocation(line: 36, column: 43, scope: !6)
!146 = !DILocation(line: 36, column: 46, scope: !6)
!147 = !DILocation(line: 36, column: 10, scope: !6)
!148 = !DILocation(line: 36, column: 2, scope: !6)
!149 = !DILocalVariable(name: "a", arg: 1, scope: !108, file: !1, line: 40, type: !10)
!150 = !DILocation(line: 40, column: 38, scope: !108)
!151 = !DILocation(line: 42, column: 11, scope: !108)
!152 = !DILocation(line: 42, column: 14, scope: !108)
!153 = !DILocation(line: 42, column: 22, scope: !108)
!154 = !DILocation(line: 42, column: 44, scope: !108)
!155 = !DILocation(line: 42, column: 10, scope: !108)
!156 = !DILocation(line: 42, column: 2, scope: !108)
!157 = !DILocalVariable(name: "a", arg: 1, scope: !109, file: !1, line: 46, type: !10)
!158 = !DILocation(line: 46, column: 37, scope: !109)
!159 = !DILocalVariable(name: "n", arg: 2, scope: !109, file: !1, line: 46, type: !9)
!160 = !DILocation(line: 46, column: 44, scope: !109)
!161 = !DILocation(line: 48, column: 11, scope: !109)
!162 = !DILocation(line: 48, column: 14, scope: !109)
!163 = !DILocation(line: 48, column: 22, scope: !109)
!164 = !DILocation(line: 48, column: 43, scope: !109)
!165 = !DILocation(line: 48, column: 46, scope: !109)
!166 = !DILocation(line: 48, column: 10, scope: !109)
!167 = !DILocation(line: 48, column: 2, scope: !109)
!168 = !DILocalVariable(name: "a", arg: 1, scope: !110, file: !1, line: 52, type: !10)
!169 = !DILocation(line: 52, column: 38, scope: !110)
!170 = !DILocalVariable(name: "n", arg: 2, scope: !110, file: !1, line: 52, type: !9)
!171 = !DILocation(line: 52, column: 45, scope: !110)
!172 = !DILocation(line: 54, column: 11, scope: !110)
!173 = !DILocation(line: 54, column: 14, scope: !110)
!174 = !DILocation(line: 54, column: 22, scope: !110)
!175 = !DILocation(line: 54, column: 44, scope: !110)
!176 = !DILocation(line: 54, column: 47, scope: !110)
!177 = !DILocation(line: 54, column: 10, scope: !110)
!178 = !DILocation(line: 54, column: 2, scope: !110)
!179 = !DILocalVariable(name: "a", arg: 1, scope: !114, file: !1, line: 58, type: !10)
!180 = !DILocation(line: 58, column: 30, scope: !114)
!181 = !DILocation(line: 60, column: 6, scope: !182)
!182 = distinct !DILexicalBlock(scope: !114, file: !1, line: 60, column: 6)
!183 = !DILocation(line: 60, column: 8, scope: !182)
!184 = !DILocation(line: 60, column: 6, scope: !114)
!185 = !DILocation(line: 61, column: 3, scope: !182)
!186 = !DILocation(line: 62, column: 11, scope: !114)
!187 = !DILocation(line: 62, column: 14, scope: !114)
!188 = !DILocation(line: 62, column: 22, scope: !114)
!189 = !DILocation(line: 62, column: 36, scope: !114)
!190 = !DILocation(line: 62, column: 10, scope: !114)
!191 = !DILocation(line: 62, column: 2, scope: !114)
!192 = !DILocation(line: 63, column: 1, scope: !114)
!193 = !DILocalVariable(name: "a", arg: 1, scope: !115, file: !1, line: 66, type: !10)
!194 = !DILocation(line: 66, column: 37, scope: !115)
!195 = !DILocation(line: 68, column: 11, scope: !115)
!196 = !DILocation(line: 68, column: 14, scope: !115)
!197 = !DILocation(line: 68, column: 22, scope: !115)
!198 = !DILocation(line: 68, column: 37, scope: !115)
!199 = !DILocation(line: 68, column: 10, scope: !115)
!200 = !DILocation(line: 68, column: 2, scope: !115)
!201 = !DILocalVariable(name: "a", arg: 1, scope: !116, file: !1, line: 72, type: !10)
!202 = !DILocation(line: 72, column: 36, scope: !116)
!203 = !DILocation(line: 74, column: 11, scope: !116)
!204 = !DILocation(line: 74, column: 14, scope: !116)
!205 = !DILocation(line: 74, column: 22, scope: !116)
!206 = !DILocation(line: 74, column: 37, scope: !116)
!207 = !DILocation(line: 74, column: 10, scope: !116)
!208 = !DILocation(line: 74, column: 2, scope: !116)
!209 = !DILocalVariable(name: "a", arg: 1, scope: !117, file: !1, line: 78, type: !10)
!210 = !DILocation(line: 78, column: 36, scope: !117)
!211 = !DILocation(line: 80, column: 2, scope: !117)
!212 = !DILocation(line: 80, column: 5, scope: !117)
!213 = !DILocation(line: 80, column: 11, scope: !117)
!214 = !DILocation(line: 81, column: 9, scope: !117)
!215 = !DILocation(line: 81, column: 12, scope: !117)
!216 = !DILocation(line: 81, column: 2, scope: !117)
!217 = !DILocalVariable(name: "a", arg: 1, scope: !118, file: !1, line: 85, type: !10)
!218 = !DILocation(line: 85, column: 36, scope: !118)
!219 = !DILocation(line: 87, column: 22, scope: !118)
!220 = !DILocation(line: 87, column: 9, scope: !118)
!221 = !DILocation(line: 87, column: 2, scope: !118)
!222 = !DILocalVariable(name: "a", arg: 1, scope: !119, file: !1, line: 93, type: !10)
!223 = !DILocation(line: 93, column: 38, scope: !119)
!224 = !DILocation(line: 95, column: 28, scope: !119)
!225 = !DILocation(line: 95, column: 9, scope: !119)
!226 = !DILocation(line: 95, column: 2, scope: !119)
!227 = !DILocalVariable(name: "a", arg: 1, scope: !120, file: !1, line: 100, type: !10)
!228 = !DILocation(line: 100, column: 35, scope: !120)
!229 = !DILocation(line: 102, column: 22, scope: !120)
!230 = !DILocation(line: 102, column: 9, scope: !120)
!231 = !DILocation(line: 102, column: 2, scope: !120)
!232 = !DILocalVariable(name: "a", arg: 1, scope: !121, file: !1, line: 108, type: !10)
!233 = !DILocation(line: 108, column: 37, scope: !121)
!234 = !DILocation(line: 110, column: 27, scope: !121)
!235 = !DILocation(line: 110, column: 9, scope: !121)
!236 = !DILocation(line: 110, column: 2, scope: !121)
!237 = !DILocalVariable(name: "a", arg: 1, scope: !122, file: !1, line: 115, type: !10)
!238 = !DILocation(line: 115, column: 38, scope: !122)
!239 = !DILocalVariable(name: "entry", arg: 2, scope: !122, file: !1, line: 115, type: !30)
!240 = !DILocation(line: 115, column: 63, scope: !122)
!241 = !DILocation(line: 117, column: 4, scope: !122)
!242 = !DILocation(line: 117, column: 7, scope: !122)
!243 = !DILocation(line: 117, column: 2, scope: !122)
!244 = !DILocation(line: 118, column: 11, scope: !122)
!245 = !DILocation(line: 118, column: 14, scope: !122)
!246 = !DILocation(line: 118, column: 22, scope: !122)
!247 = !DILocation(line: 118, column: 44, scope: !122)
!248 = !DILocation(line: 118, column: 47, scope: !122)
!249 = !DILocation(line: 118, column: 10, scope: !122)
!250 = !DILocation(line: 118, column: 2, scope: !122)
!251 = !DILocalVariable(name: "a", arg: 1, scope: !123, file: !1, line: 122, type: !10)
!252 = !DILocation(line: 122, column: 44, scope: !123)
!253 = !DILocation(line: 124, column: 11, scope: !123)
!254 = !DILocation(line: 124, column: 14, scope: !123)
!255 = !DILocation(line: 124, column: 22, scope: !123)
!256 = !DILocation(line: 124, column: 50, scope: !123)
!257 = !DILocation(line: 124, column: 10, scope: !123)
!258 = !DILocation(line: 124, column: 2, scope: !123)
!259 = !DILocalVariable(name: "a", arg: 1, scope: !124, file: !1, line: 128, type: !10)
!260 = !DILocation(line: 128, column: 36, scope: !124)
!261 = !DILocalVariable(name: "buff", arg: 2, scope: !124, file: !1, line: 128, type: !43)
!262 = !DILocation(line: 128, column: 51, scope: !124)
!263 = !DILocalVariable(name: "s", arg: 3, scope: !124, file: !1, line: 128, type: !45)
!264 = !DILocation(line: 128, column: 64, scope: !124)
!265 = !DILocation(line: 130, column: 11, scope: !124)
!266 = !DILocation(line: 130, column: 14, scope: !124)
!267 = !DILocation(line: 130, column: 22, scope: !124)
!268 = !DILocation(line: 130, column: 42, scope: !124)
!269 = !DILocation(line: 130, column: 45, scope: !124)
!270 = !DILocation(line: 130, column: 51, scope: !124)
!271 = !DILocation(line: 130, column: 10, scope: !124)
!272 = !DILocation(line: 130, column: 2, scope: !124)
!273 = !DILocalVariable(name: "a", arg: 1, scope: !128, file: !1, line: 134, type: !10)
!274 = !DILocation(line: 134, column: 42, scope: !128)
!275 = !DILocalVariable(name: "buff", arg: 2, scope: !128, file: !1, line: 134, type: !43)
!276 = !DILocation(line: 134, column: 57, scope: !128)
!277 = !DILocalVariable(name: "s", arg: 3, scope: !128, file: !1, line: 134, type: !45)
!278 = !DILocation(line: 134, column: 70, scope: !128)
!279 = !DILocalVariable(name: "o", arg: 4, scope: !128, file: !1, line: 134, type: !52)
!280 = !DILocation(line: 134, column: 81, scope: !128)
!281 = !DILocation(line: 136, column: 6, scope: !282)
!282 = distinct !DILexicalBlock(scope: !128, file: !1, line: 136, column: 6)
!283 = !DILocation(line: 136, column: 9, scope: !282)
!284 = !DILocation(line: 136, column: 17, scope: !282)
!285 = !DILocation(line: 136, column: 42, scope: !282)
!286 = !DILocation(line: 136, column: 6, scope: !128)
!287 = !DILocation(line: 137, column: 21, scope: !288)
!288 = distinct !DILexicalBlock(scope: !282, file: !1, line: 136, column: 51)
!289 = !DILocation(line: 137, column: 3, scope: !288)
!290 = !DILocation(line: 139, column: 3, scope: !288)
!291 = !DILocation(line: 139, column: 6, scope: !288)
!292 = !DILocation(line: 139, column: 12, scope: !288)
!293 = !DILocation(line: 140, column: 3, scope: !288)
!294 = !DILocation(line: 142, column: 11, scope: !128)
!295 = !DILocation(line: 142, column: 14, scope: !128)
!296 = !DILocation(line: 142, column: 22, scope: !128)
!297 = !DILocation(line: 142, column: 48, scope: !128)
!298 = !DILocation(line: 142, column: 51, scope: !128)
!299 = !DILocation(line: 142, column: 57, scope: !128)
!300 = !DILocation(line: 142, column: 60, scope: !128)
!301 = !DILocation(line: 142, column: 10, scope: !128)
!302 = !DILocation(line: 142, column: 2, scope: !128)
!303 = !DILocation(line: 143, column: 1, scope: !128)
!304 = !DILocalVariable(name: "a", arg: 1, scope: !131, file: !1, line: 146, type: !10)
!305 = !DILocation(line: 146, column: 42, scope: !131)
!306 = !DILocalVariable(name: "entry", arg: 2, scope: !131, file: !1, line: 146, type: !58)
!307 = !DILocation(line: 146, column: 68, scope: !131)
!308 = !DILocation(line: 148, column: 11, scope: !131)
!309 = !DILocation(line: 148, column: 14, scope: !131)
!310 = !DILocation(line: 148, column: 22, scope: !131)
!311 = !DILocation(line: 148, column: 48, scope: !131)
!312 = !DILocation(line: 148, column: 51, scope: !131)
!313 = !DILocation(line: 148, column: 10, scope: !131)
!314 = !DILocation(line: 148, column: 2, scope: !131)
!315 = !DILocalVariable(name: "a", arg: 1, scope: !132, file: !1, line: 152, type: !10)
!316 = !DILocation(line: 152, column: 43, scope: !132)
!317 = !DILocalVariable(name: "entry", arg: 2, scope: !132, file: !1, line: 152, type: !30)
!318 = !DILocation(line: 152, column: 68, scope: !132)
!319 = !DILocation(line: 154, column: 11, scope: !132)
!320 = !DILocation(line: 154, column: 14, scope: !132)
!321 = !DILocation(line: 154, column: 22, scope: !132)
!322 = !DILocation(line: 154, column: 49, scope: !132)
!323 = !DILocation(line: 154, column: 52, scope: !132)
!324 = !DILocation(line: 154, column: 10, scope: !132)
!325 = !DILocation(line: 154, column: 2, scope: !132)
!326 = !DILocalVariable(name: "a", arg: 1, scope: !133, file: !1, line: 158, type: !10)
!327 = !DILocation(line: 158, column: 41, scope: !133)
!328 = !DILocalVariable(name: "buff", arg: 2, scope: !133, file: !1, line: 159, type: !64)
!329 = !DILocation(line: 159, column: 18, scope: !133)
!330 = !DILocalVariable(name: "s", arg: 3, scope: !133, file: !1, line: 159, type: !65)
!331 = !DILocation(line: 159, column: 32, scope: !133)
!332 = !DILocalVariable(name: "o", arg: 4, scope: !133, file: !1, line: 159, type: !66)
!333 = !DILocation(line: 159, column: 44, scope: !133)
!334 = !DILocation(line: 161, column: 11, scope: !133)
!335 = !DILocation(line: 161, column: 14, scope: !133)
!336 = !DILocation(line: 161, column: 22, scope: !133)
!337 = !DILocation(line: 161, column: 47, scope: !133)
!338 = !DILocation(line: 161, column: 50, scope: !133)
!339 = !DILocation(line: 161, column: 56, scope: !133)
!340 = !DILocation(line: 161, column: 59, scope: !133)
!341 = !DILocation(line: 161, column: 10, scope: !133)
!342 = !DILocation(line: 161, column: 2, scope: !133)
