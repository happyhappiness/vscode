; ModuleID = '/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_set_format_filter_by_ext.c'
target datalayout = "e-m:e-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-unknown-linux-gnu"

%struct.anon = type { i8*, i32 (%struct.archive*)*, i32 (%struct.archive*)* }
%struct.archive = type { i32, i32, %struct.archive_vtable*, i32, i8*, i32, i8*, i32, i32, i8*, %struct.archive_string, i8*, i32, i32, %struct.archive_string_conv*, i8*, i64, i64, i64, i8, i64 }
%struct.archive_vtable = type { i32 (%struct.archive*)*, i32 (%struct.archive*)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*)*, i64 (%struct.archive*, i8*, i64)*, i64 (%struct.archive*, i8*, i64, i64)*, i32 (%struct.archive*, %struct.archive_entry**)*, i32 (%struct.archive*, %struct.archive_entry*)*, i32 (%struct.archive*, i8**, i64*, i64*)*, i32 (%struct.archive*)*, i64 (%struct.archive*, i32)*, i32 (%struct.archive*, i32)*, i8* (%struct.archive*, i32)* }
%struct.archive_entry = type opaque
%struct.archive_string = type { i8*, i64, i64 }
%struct.archive_string_conv = type opaque

@names = internal global [13 x %struct.anon] [%struct.anon { i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.1, i32 0, i32 0), i32 (%struct.archive*)* @archive_write_set_format_7zip, i32 (%struct.archive*)* @archive_write_add_filter_none }, %struct.anon { i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.2, i32 0, i32 0), i32 (%struct.archive*)* @archive_write_set_format_zip, i32 (%struct.archive*)* @archive_write_add_filter_none }, %struct.anon { i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.3, i32 0, i32 0), i32 (%struct.archive*)* @archive_write_set_format_zip, i32 (%struct.archive*)* @archive_write_add_filter_none }, %struct.anon { i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.4, i32 0, i32 0), i32 (%struct.archive*)* @archive_write_set_format_cpio, i32 (%struct.archive*)* @archive_write_add_filter_none }, %struct.anon { i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.5, i32 0, i32 0), i32 (%struct.archive*)* @archive_write_set_format_iso9660, i32 (%struct.archive*)* @archive_write_add_filter_none }, %struct.anon { i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.6, i32 0, i32 0), i32 (%struct.archive*)* @archive_write_set_format_ar_svr4, i32 (%struct.archive*)* @archive_write_add_filter_none }, %struct.anon { i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.7, i32 0, i32 0), i32 (%struct.archive*)* @archive_write_set_format_ar_svr4, i32 (%struct.archive*)* @archive_write_add_filter_none }, %struct.anon { i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.8, i32 0, i32 0), i32 (%struct.archive*)* @archive_write_set_format_pax_restricted, i32 (%struct.archive*)* @archive_write_add_filter_none }, %struct.anon { i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.9, i32 0, i32 0), i32 (%struct.archive*)* @archive_write_set_format_pax_restricted, i32 (%struct.archive*)* @archive_write_add_filter_gzip }, %struct.anon { i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.10, i32 0, i32 0), i32 (%struct.archive*)* @archive_write_set_format_pax_restricted, i32 (%struct.archive*)* @archive_write_add_filter_gzip }, %struct.anon { i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.11, i32 0, i32 0), i32 (%struct.archive*)* @archive_write_set_format_pax_restricted, i32 (%struct.archive*)* @archive_write_add_filter_bzip2 }, %struct.anon { i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.12, i32 0, i32 0), i32 (%struct.archive*)* @archive_write_set_format_pax_restricted, i32 (%struct.archive*)* @archive_write_add_filter_xz }, %struct.anon zeroinitializer], align 16
@.str = private unnamed_addr constant [20 x i8] c"No such format '%s'\00", align 1
@.str.1 = private unnamed_addr constant [4 x i8] c".7z\00", align 1
@.str.2 = private unnamed_addr constant [5 x i8] c".zip\00", align 1
@.str.3 = private unnamed_addr constant [5 x i8] c".jar\00", align 1
@.str.4 = private unnamed_addr constant [6 x i8] c".cpio\00", align 1
@.str.5 = private unnamed_addr constant [5 x i8] c".iso\00", align 1
@.str.6 = private unnamed_addr constant [3 x i8] c".a\00", align 1
@.str.7 = private unnamed_addr constant [4 x i8] c".ar\00", align 1
@.str.8 = private unnamed_addr constant [5 x i8] c".tar\00", align 1
@.str.9 = private unnamed_addr constant [5 x i8] c".tgz\00", align 1
@.str.10 = private unnamed_addr constant [8 x i8] c".tar.gz\00", align 1
@.str.11 = private unnamed_addr constant [9 x i8] c".tar.bz2\00", align 1
@.str.12 = private unnamed_addr constant [8 x i8] c".tar.xz\00", align 1

; Function Attrs: nounwind uwtable
define i32 @archive_write_set_format_filter_by_ext(%struct.archive* %a, i8* %filename) #0 !dbg !6 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive*, align 8
  %filename.addr = alloca i8*, align 8
  %names_index = alloca i32, align 4
  %format_state = alloca i32, align 4
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !132, metadata !133), !dbg !134
  store i8* %filename, i8** %filename.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %filename.addr, metadata !135, metadata !133), !dbg !136
  call void @llvm.dbg.declare(metadata i32* %names_index, metadata !137, metadata !133), !dbg !138
  %0 = load i8*, i8** %filename.addr, align 8, !dbg !139
  %call = call i32 @get_array_index(i8* %0), !dbg !140
  store i32 %call, i32* %names_index, align 4, !dbg !138
  %1 = load i32, i32* %names_index, align 4, !dbg !141
  %cmp = icmp sge i32 %1, 0, !dbg !143
  br i1 %cmp, label %if.then, label %if.end, !dbg !144

if.then:                                          ; preds = %entry
  call void @llvm.dbg.declare(metadata i32* %format_state, metadata !145, metadata !133), !dbg !147
  %2 = load i32, i32* %names_index, align 4, !dbg !148
  %idxprom = sext i32 %2 to i64, !dbg !149
  %arrayidx = getelementptr inbounds [13 x %struct.anon], [13 x %struct.anon]* @names, i64 0, i64 %idxprom, !dbg !149
  %format = getelementptr inbounds %struct.anon, %struct.anon* %arrayidx, i32 0, i32 1, !dbg !150
  %3 = load i32 (%struct.archive*)*, i32 (%struct.archive*)** %format, align 8, !dbg !150
  %4 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !151
  %call1 = call i32 %3(%struct.archive* %4), !dbg !152
  store i32 %call1, i32* %format_state, align 4, !dbg !147
  %5 = load i32, i32* %format_state, align 4, !dbg !153
  %cmp2 = icmp eq i32 %5, 0, !dbg !155
  br i1 %cmp2, label %if.then3, label %if.else, !dbg !156

if.then3:                                         ; preds = %if.then
  %6 = load i32, i32* %names_index, align 4, !dbg !157
  %idxprom4 = sext i32 %6 to i64, !dbg !158
  %arrayidx5 = getelementptr inbounds [13 x %struct.anon], [13 x %struct.anon]* @names, i64 0, i64 %idxprom4, !dbg !158
  %filter = getelementptr inbounds %struct.anon, %struct.anon* %arrayidx5, i32 0, i32 2, !dbg !159
  %7 = load i32 (%struct.archive*)*, i32 (%struct.archive*)** %filter, align 8, !dbg !159
  %8 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !160
  %call6 = call i32 %7(%struct.archive* %8), !dbg !161
  store i32 %call6, i32* %retval, align 4, !dbg !162
  br label %return, !dbg !162

if.else:                                          ; preds = %if.then
  %9 = load i32, i32* %format_state, align 4, !dbg !163
  store i32 %9, i32* %retval, align 4, !dbg !164
  br label %return, !dbg !164

if.end:                                           ; preds = %entry
  %10 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !165
  %11 = load i8*, i8** %filename.addr, align 8, !dbg !166
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %10, i32 22, i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str, i32 0, i32 0), i8* %11), !dbg !167
  %12 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !168
  %state = getelementptr inbounds %struct.archive, %struct.archive* %12, i32 0, i32 1, !dbg !169
  store i32 32768, i32* %state, align 4, !dbg !170
  store i32 -30, i32* %retval, align 4, !dbg !171
  br label %return, !dbg !171

return:                                           ; preds = %if.end, %if.else, %if.then3
  %13 = load i32, i32* %retval, align 4, !dbg !172
  ret i32 %13, !dbg !172
}

; Function Attrs: nounwind readnone
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: nounwind uwtable
define internal i32 @get_array_index(i8* %name) #0 !dbg !113 {
entry:
  %retval = alloca i32, align 4
  %name.addr = alloca i8*, align 8
  %i = alloca i32, align 4
  store i8* %name, i8** %name.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %name.addr, metadata !173, metadata !133), !dbg !174
  call void @llvm.dbg.declare(metadata i32* %i, metadata !175, metadata !133), !dbg !176
  store i32 0, i32* %i, align 4, !dbg !177
  br label %for.cond, !dbg !179

for.cond:                                         ; preds = %for.inc, %entry
  %0 = load i32, i32* %i, align 4, !dbg !180
  %idxprom = sext i32 %0 to i64, !dbg !183
  %arrayidx = getelementptr inbounds [13 x %struct.anon], [13 x %struct.anon]* @names, i64 0, i64 %idxprom, !dbg !183
  %name1 = getelementptr inbounds %struct.anon, %struct.anon* %arrayidx, i32 0, i32 0, !dbg !184
  %1 = load i8*, i8** %name1, align 8, !dbg !184
  %cmp = icmp ne i8* %1, null, !dbg !185
  br i1 %cmp, label %for.body, label %for.end, !dbg !186

for.body:                                         ; preds = %for.cond
  %2 = load i8*, i8** %name.addr, align 8, !dbg !187
  %3 = load i32, i32* %i, align 4, !dbg !190
  %idxprom2 = sext i32 %3 to i64, !dbg !191
  %arrayidx3 = getelementptr inbounds [13 x %struct.anon], [13 x %struct.anon]* @names, i64 0, i64 %idxprom2, !dbg !191
  %name4 = getelementptr inbounds %struct.anon, %struct.anon* %arrayidx3, i32 0, i32 0, !dbg !192
  %4 = load i8*, i8** %name4, align 8, !dbg !192
  %call = call i32 @cmpsuff(i8* %2, i8* %4), !dbg !193
  %cmp5 = icmp eq i32 %call, 0, !dbg !194
  br i1 %cmp5, label %if.then, label %if.end, !dbg !195

if.then:                                          ; preds = %for.body
  %5 = load i32, i32* %i, align 4, !dbg !196
  store i32 %5, i32* %retval, align 4, !dbg !197
  br label %return, !dbg !197

if.end:                                           ; preds = %for.body
  br label %for.inc, !dbg !198

for.inc:                                          ; preds = %if.end
  %6 = load i32, i32* %i, align 4, !dbg !199
  %inc = add nsw i32 %6, 1, !dbg !199
  store i32 %inc, i32* %i, align 4, !dbg !199
  br label %for.cond, !dbg !201

for.end:                                          ; preds = %for.cond
  store i32 -1, i32* %retval, align 4, !dbg !202
  br label %return, !dbg !202

return:                                           ; preds = %for.end, %if.then
  %7 = load i32, i32* %retval, align 4, !dbg !203
  ret i32 %7, !dbg !203
}

declare void @archive_set_error(%struct.archive*, i32, i8*, ...) #2

; Function Attrs: nounwind uwtable
define i32 @archive_write_set_format_filter_by_ext_def(%struct.archive* %a, i8* %filename, i8* %def_ext) #0 !dbg !110 {
entry:
  %retval = alloca i32, align 4
  %a.addr = alloca %struct.archive*, align 8
  %filename.addr = alloca i8*, align 8
  %def_ext.addr = alloca i8*, align 8
  %names_index = alloca i32, align 4
  %format_state = alloca i32, align 4
  store %struct.archive* %a, %struct.archive** %a.addr, align 8
  call void @llvm.dbg.declare(metadata %struct.archive** %a.addr, metadata !204, metadata !133), !dbg !205
  store i8* %filename, i8** %filename.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %filename.addr, metadata !206, metadata !133), !dbg !207
  store i8* %def_ext, i8** %def_ext.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %def_ext.addr, metadata !208, metadata !133), !dbg !209
  call void @llvm.dbg.declare(metadata i32* %names_index, metadata !210, metadata !133), !dbg !211
  %0 = load i8*, i8** %filename.addr, align 8, !dbg !212
  %call = call i32 @get_array_index(i8* %0), !dbg !213
  store i32 %call, i32* %names_index, align 4, !dbg !211
  %1 = load i32, i32* %names_index, align 4, !dbg !214
  %cmp = icmp slt i32 %1, 0, !dbg !216
  br i1 %cmp, label %if.then, label %if.end, !dbg !217

if.then:                                          ; preds = %entry
  %2 = load i8*, i8** %def_ext.addr, align 8, !dbg !218
  %call1 = call i32 @get_array_index(i8* %2), !dbg !219
  store i32 %call1, i32* %names_index, align 4, !dbg !220
  br label %if.end, !dbg !221

if.end:                                           ; preds = %if.then, %entry
  %3 = load i32, i32* %names_index, align 4, !dbg !222
  %cmp2 = icmp sge i32 %3, 0, !dbg !224
  br i1 %cmp2, label %if.then3, label %if.end10, !dbg !225

if.then3:                                         ; preds = %if.end
  call void @llvm.dbg.declare(metadata i32* %format_state, metadata !226, metadata !133), !dbg !228
  %4 = load i32, i32* %names_index, align 4, !dbg !229
  %idxprom = sext i32 %4 to i64, !dbg !230
  %arrayidx = getelementptr inbounds [13 x %struct.anon], [13 x %struct.anon]* @names, i64 0, i64 %idxprom, !dbg !230
  %format = getelementptr inbounds %struct.anon, %struct.anon* %arrayidx, i32 0, i32 1, !dbg !231
  %5 = load i32 (%struct.archive*)*, i32 (%struct.archive*)** %format, align 8, !dbg !231
  %6 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !232
  %call4 = call i32 %5(%struct.archive* %6), !dbg !233
  store i32 %call4, i32* %format_state, align 4, !dbg !228
  %7 = load i32, i32* %format_state, align 4, !dbg !234
  %cmp5 = icmp eq i32 %7, 0, !dbg !236
  br i1 %cmp5, label %if.then6, label %if.else, !dbg !237

if.then6:                                         ; preds = %if.then3
  %8 = load i32, i32* %names_index, align 4, !dbg !238
  %idxprom7 = sext i32 %8 to i64, !dbg !239
  %arrayidx8 = getelementptr inbounds [13 x %struct.anon], [13 x %struct.anon]* @names, i64 0, i64 %idxprom7, !dbg !239
  %filter = getelementptr inbounds %struct.anon, %struct.anon* %arrayidx8, i32 0, i32 2, !dbg !240
  %9 = load i32 (%struct.archive*)*, i32 (%struct.archive*)** %filter, align 8, !dbg !240
  %10 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !241
  %call9 = call i32 %9(%struct.archive* %10), !dbg !242
  store i32 %call9, i32* %retval, align 4, !dbg !243
  br label %return, !dbg !243

if.else:                                          ; preds = %if.then3
  %11 = load i32, i32* %format_state, align 4, !dbg !244
  store i32 %11, i32* %retval, align 4, !dbg !245
  br label %return, !dbg !245

if.end10:                                         ; preds = %if.end
  %12 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !246
  %13 = load i8*, i8** %filename.addr, align 8, !dbg !247
  call void (%struct.archive*, i32, i8*, ...) @archive_set_error(%struct.archive* %12, i32 22, i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str, i32 0, i32 0), i8* %13), !dbg !248
  %14 = load %struct.archive*, %struct.archive** %a.addr, align 8, !dbg !249
  %state = getelementptr inbounds %struct.archive, %struct.archive* %14, i32 0, i32 1, !dbg !250
  store i32 32768, i32* %state, align 4, !dbg !251
  store i32 -30, i32* %retval, align 4, !dbg !252
  br label %return, !dbg !252

return:                                           ; preds = %if.end10, %if.else, %if.then6
  %15 = load i32, i32* %retval, align 4, !dbg !253
  ret i32 %15, !dbg !253
}

; Function Attrs: nounwind uwtable
define internal i32 @cmpsuff(i8* %str, i8* %suffix) #0 !dbg !116 {
entry:
  %retval = alloca i32, align 4
  %str.addr = alloca i8*, align 8
  %suffix.addr = alloca i8*, align 8
  %length_str = alloca i64, align 8
  %length_suffix = alloca i64, align 8
  store i8* %str, i8** %str.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %str.addr, metadata !254, metadata !133), !dbg !255
  store i8* %suffix, i8** %suffix.addr, align 8
  call void @llvm.dbg.declare(metadata i8** %suffix.addr, metadata !256, metadata !133), !dbg !257
  call void @llvm.dbg.declare(metadata i64* %length_str, metadata !258, metadata !133), !dbg !259
  call void @llvm.dbg.declare(metadata i64* %length_suffix, metadata !260, metadata !133), !dbg !261
  %0 = load i8*, i8** %str.addr, align 8, !dbg !262
  %cmp = icmp eq i8* %0, null, !dbg !264
  br i1 %cmp, label %if.then, label %lor.lhs.false, !dbg !265

lor.lhs.false:                                    ; preds = %entry
  %1 = load i8*, i8** %suffix.addr, align 8, !dbg !266
  %cmp1 = icmp eq i8* %1, null, !dbg !268
  br i1 %cmp1, label %if.then, label %if.end, !dbg !269

if.then:                                          ; preds = %lor.lhs.false, %entry
  store i32 -1, i32* %retval, align 4, !dbg !270
  br label %return, !dbg !270

if.end:                                           ; preds = %lor.lhs.false
  %2 = load i8*, i8** %str.addr, align 8, !dbg !271
  %call = call i64 @strlen(i8* %2) #4, !dbg !272
  store i64 %call, i64* %length_str, align 8, !dbg !273
  %3 = load i8*, i8** %suffix.addr, align 8, !dbg !274
  %call2 = call i64 @strlen(i8* %3) #4, !dbg !275
  store i64 %call2, i64* %length_suffix, align 8, !dbg !276
  %4 = load i64, i64* %length_str, align 8, !dbg !277
  %5 = load i64, i64* %length_suffix, align 8, !dbg !279
  %cmp3 = icmp uge i64 %4, %5, !dbg !280
  br i1 %cmp3, label %if.then4, label %if.else, !dbg !281

if.then4:                                         ; preds = %if.end
  %6 = load i8*, i8** %str.addr, align 8, !dbg !282
  %7 = load i64, i64* %length_str, align 8, !dbg !284
  %8 = load i64, i64* %length_suffix, align 8, !dbg !285
  %sub = sub i64 %7, %8, !dbg !286
  %add.ptr = getelementptr inbounds i8, i8* %6, i64 %sub, !dbg !287
  %9 = load i8*, i8** %suffix.addr, align 8, !dbg !288
  %call5 = call i32 @strcmp(i8* %add.ptr, i8* %9) #4, !dbg !289
  store i32 %call5, i32* %retval, align 4, !dbg !290
  br label %return, !dbg !290

if.else:                                          ; preds = %if.end
  store i32 -1, i32* %retval, align 4, !dbg !291
  br label %return, !dbg !291

return:                                           ; preds = %if.else, %if.then4, %if.then
  %10 = load i32, i32* %retval, align 4, !dbg !293
  ret i32 %10, !dbg !293
}

; Function Attrs: nounwind readonly
declare i64 @strlen(i8*) #3

; Function Attrs: nounwind readonly
declare i32 @strcmp(i8*, i8*) #3

declare i32 @archive_write_set_format_7zip(%struct.archive*) #2

declare i32 @archive_write_add_filter_none(%struct.archive*) #2

declare i32 @archive_write_set_format_zip(%struct.archive*) #2

declare i32 @archive_write_set_format_cpio(%struct.archive*) #2

declare i32 @archive_write_set_format_iso9660(%struct.archive*) #2

declare i32 @archive_write_set_format_ar_svr4(%struct.archive*) #2

declare i32 @archive_write_set_format_pax_restricted(%struct.archive*) #2

declare i32 @archive_write_add_filter_gzip(%struct.archive*) #2

declare i32 @archive_write_add_filter_bzip2(%struct.archive*) #2

declare i32 @archive_write_add_filter_xz(%struct.archive*) #2

attributes #0 = { nounwind uwtable "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind readnone }
attributes #2 = { "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind readonly "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+fxsr,+mmx,+sse,+sse2" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readonly }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!129, !130}
!llvm.ident = !{!131}

!0 = distinct !DICompileUnit(language: DW_LANG_C99, file: !1, producer: "clang version 3.8.0 (tags/RELEASE_380/final)", isOptimized: false, runtimeVersion: 0, emissionKind: 1, enums: !2, retainedTypes: !3, subprograms: !5, globals: !119)
!1 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_write_set_format_filter_by_ext.c", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!2 = !{}
!3 = !{!4}
!4 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64, align: 64)
!5 = !{!6, !110, !113, !116}
!6 = distinct !DISubprogram(name: "archive_write_set_format_filter_by_ext", scope: !1, file: !1, line: 100, type: !7, isLocal: false, isDefinition: true, scopeLine: 101, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!7 = !DISubroutineType(types: !8)
!8 = !{!9, !10, !80}
!9 = !DIBasicType(name: "int", size: 32, align: 32, encoding: DW_ATE_signed)
!10 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !11, size: 64, align: 64)
!11 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive", file: !12, line: 89, size: 1280, align: 64, elements: !13)
!12 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_private.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!13 = !{!14, !16, !17, !83, !84, !85, !86, !87, !88, !89, !90, !98, !99, !100, !101, !104, !105, !106, !107, !108, !109}
!14 = !DIDerivedType(tag: DW_TAG_member, name: "magic", scope: !11, file: !12, line: 96, baseType: !15, size: 32, align: 32)
!15 = !DIBasicType(name: "unsigned int", size: 32, align: 32, encoding: DW_ATE_unsigned)
!16 = !DIDerivedType(tag: DW_TAG_member, name: "state", scope: !11, file: !12, line: 97, baseType: !15, size: 32, align: 32, offset: 32)
!17 = !DIDerivedType(tag: DW_TAG_member, name: "vtable", scope: !11, file: !12, line: 103, baseType: !18, size: 64, align: 64, offset: 64)
!18 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !19, size: 64, align: 64)
!19 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_vtable", file: !12, line: 63, size: 832, align: 64, elements: !20)
!20 = !{!21, !25, !26, !33, !34, !48, !54, !59, !60, !67, !68, !72, !76}
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
!38 = !DIDerivedType(tag: DW_TAG_typedef, name: "ssize_t", file: !39, line: 109, baseType: !40)
!39 = !DIFile(filename: "/usr/include/x86_64-linux-gnu/sys/types.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
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
!73 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !74, size: 64, align: 64)
!74 = !DISubroutineType(types: !75)
!75 = !{!9, !10, !9}
!76 = !DIDerivedType(tag: DW_TAG_member, name: "archive_filter_name", scope: !19, file: !12, line: 84, baseType: !77, size: 64, align: 64, offset: 768)
!77 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !78, size: 64, align: 64)
!78 = !DISubroutineType(types: !79)
!79 = !{!80, !10, !9}
!80 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !81, size: 64, align: 64)
!81 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !82)
!82 = !DIBasicType(name: "char", size: 8, align: 8, encoding: DW_ATE_signed_char)
!83 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format", scope: !11, file: !12, line: 105, baseType: !9, size: 32, align: 32, offset: 128)
!84 = !DIDerivedType(tag: DW_TAG_member, name: "archive_format_name", scope: !11, file: !12, line: 106, baseType: !80, size: 64, align: 64, offset: 192)
!85 = !DIDerivedType(tag: DW_TAG_member, name: "compression_code", scope: !11, file: !12, line: 108, baseType: !9, size: 32, align: 32, offset: 256)
!86 = !DIDerivedType(tag: DW_TAG_member, name: "compression_name", scope: !11, file: !12, line: 109, baseType: !80, size: 64, align: 64, offset: 320)
!87 = !DIDerivedType(tag: DW_TAG_member, name: "file_count", scope: !11, file: !12, line: 112, baseType: !9, size: 32, align: 32, offset: 384)
!88 = !DIDerivedType(tag: DW_TAG_member, name: "archive_error_number", scope: !11, file: !12, line: 114, baseType: !9, size: 32, align: 32, offset: 416)
!89 = !DIDerivedType(tag: DW_TAG_member, name: "error", scope: !11, file: !12, line: 115, baseType: !80, size: 64, align: 64, offset: 448)
!90 = !DIDerivedType(tag: DW_TAG_member, name: "error_string", scope: !11, file: !12, line: 116, baseType: !91, size: 192, align: 64, offset: 512)
!91 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string", file: !92, line: 58, size: 192, align: 64, elements: !93)
!92 = !DIFile(filename: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive/archive_string.h", directory: "/data/download/cmake/cmake-master/Utilities/cmlibarchive/libarchive")
!93 = !{!94, !96, !97}
!94 = !DIDerivedType(tag: DW_TAG_member, name: "s", scope: !91, file: !92, line: 59, baseType: !95, size: 64, align: 64)
!95 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !82, size: 64, align: 64)
!96 = !DIDerivedType(tag: DW_TAG_member, name: "length", scope: !91, file: !92, line: 60, baseType: !45, size: 64, align: 64, offset: 64)
!97 = !DIDerivedType(tag: DW_TAG_member, name: "buffer_length", scope: !91, file: !92, line: 61, baseType: !45, size: 64, align: 64, offset: 128)
!98 = !DIDerivedType(tag: DW_TAG_member, name: "current_code", scope: !11, file: !12, line: 118, baseType: !95, size: 64, align: 64, offset: 704)
!99 = !DIDerivedType(tag: DW_TAG_member, name: "current_codepage", scope: !11, file: !12, line: 119, baseType: !15, size: 32, align: 32, offset: 768)
!100 = !DIDerivedType(tag: DW_TAG_member, name: "current_oemcp", scope: !11, file: !12, line: 120, baseType: !15, size: 32, align: 32, offset: 800)
!101 = !DIDerivedType(tag: DW_TAG_member, name: "sconv", scope: !11, file: !12, line: 121, baseType: !102, size: 64, align: 64, offset: 832)
!102 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !103, size: 64, align: 64)
!103 = !DICompositeType(tag: DW_TAG_structure_type, name: "archive_string_conv", file: !92, line: 70, flags: DIFlagFwdDecl)
!104 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_block", scope: !11, file: !12, line: 127, baseType: !80, size: 64, align: 64, offset: 896)
!105 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_offset", scope: !11, file: !12, line: 128, baseType: !52, size: 64, align: 64, offset: 960)
!106 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_output_offset", scope: !11, file: !12, line: 129, baseType: !52, size: 64, align: 64, offset: 1024)
!107 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_remaining", scope: !11, file: !12, line: 130, baseType: !45, size: 64, align: 64, offset: 1088)
!108 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_is_posix_read", scope: !11, file: !12, line: 137, baseType: !82, size: 8, align: 8, offset: 1152)
!109 = !DIDerivedType(tag: DW_TAG_member, name: "read_data_requested", scope: !11, file: !12, line: 138, baseType: !45, size: 64, align: 64, offset: 1216)
!110 = distinct !DISubprogram(name: "archive_write_set_format_filter_by_ext_def", scope: !1, file: !1, line: 119, type: !111, isLocal: false, isDefinition: true, scopeLine: 120, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!111 = !DISubroutineType(types: !112)
!112 = !{!9, !10, !80, !80}
!113 = distinct !DISubprogram(name: "get_array_index", scope: !1, file: !1, line: 86, type: !114, isLocal: true, isDefinition: true, scopeLine: 87, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!114 = !DISubroutineType(types: !115)
!115 = !{!9, !80}
!116 = distinct !DISubprogram(name: "cmpsuff", scope: !1, file: !1, line: 69, type: !117, isLocal: true, isDefinition: true, scopeLine: 70, flags: DIFlagPrototyped, isOptimized: false, variables: !2)
!117 = !DISubroutineType(types: !118)
!118 = !{!9, !80, !80}
!119 = !{!120}
!120 = !DIGlobalVariable(name: "names", scope: !0, file: !1, line: 46, type: !121, isLocal: true, isDefinition: true, variable: [13 x %struct.anon]* @names)
!121 = !DICompositeType(tag: DW_TAG_array_type, baseType: !122, size: 2496, align: 64, elements: !127)
!122 = !DICompositeType(tag: DW_TAG_structure_type, file: !1, line: 46, size: 192, align: 64, elements: !123)
!123 = !{!124, !125, !126}
!124 = !DIDerivedType(tag: DW_TAG_member, name: "name", scope: !122, file: !1, line: 46, baseType: !80, size: 64, align: 64)
!125 = !DIDerivedType(tag: DW_TAG_member, name: "format", scope: !122, file: !1, line: 46, baseType: !22, size: 64, align: 64, offset: 64)
!126 = !DIDerivedType(tag: DW_TAG_member, name: "filter", scope: !122, file: !1, line: 46, baseType: !22, size: 64, align: 64, offset: 128)
!127 = !{!128}
!128 = !DISubrange(count: 13)
!129 = !{i32 2, !"Dwarf Version", i32 4}
!130 = !{i32 2, !"Debug Info Version", i32 3}
!131 = !{!"clang version 3.8.0 (tags/RELEASE_380/final)"}
!132 = !DILocalVariable(name: "a", arg: 1, scope: !6, file: !1, line: 100, type: !10)
!133 = !DIExpression()
!134 = !DILocation(line: 100, column: 56, scope: !6)
!135 = !DILocalVariable(name: "filename", arg: 2, scope: !6, file: !1, line: 100, type: !80)
!136 = !DILocation(line: 100, column: 71, scope: !6)
!137 = !DILocalVariable(name: "names_index", scope: !6, file: !1, line: 102, type: !9)
!138 = !DILocation(line: 102, column: 7, scope: !6)
!139 = !DILocation(line: 102, column: 37, scope: !6)
!140 = !DILocation(line: 102, column: 21, scope: !6)
!141 = !DILocation(line: 104, column: 7, scope: !142)
!142 = distinct !DILexicalBlock(scope: !6, file: !1, line: 104, column: 7)
!143 = !DILocation(line: 104, column: 19, scope: !142)
!144 = !DILocation(line: 104, column: 7, scope: !6)
!145 = !DILocalVariable(name: "format_state", scope: !146, file: !1, line: 106, type: !9)
!146 = distinct !DILexicalBlock(scope: !142, file: !1, line: 105, column: 3)
!147 = !DILocation(line: 106, column: 9, scope: !146)
!148 = !DILocation(line: 106, column: 31, scope: !146)
!149 = !DILocation(line: 106, column: 25, scope: !146)
!150 = !DILocation(line: 106, column: 44, scope: !146)
!151 = !DILocation(line: 106, column: 52, scope: !146)
!152 = !DILocation(line: 106, column: 24, scope: !146)
!153 = !DILocation(line: 107, column: 9, scope: !154)
!154 = distinct !DILexicalBlock(scope: !146, file: !1, line: 107, column: 9)
!155 = !DILocation(line: 107, column: 22, scope: !154)
!156 = !DILocation(line: 107, column: 9, scope: !146)
!157 = !DILocation(line: 108, column: 22, scope: !154)
!158 = !DILocation(line: 108, column: 16, scope: !154)
!159 = !DILocation(line: 108, column: 35, scope: !154)
!160 = !DILocation(line: 108, column: 43, scope: !154)
!161 = !DILocation(line: 108, column: 15, scope: !154)
!162 = !DILocation(line: 108, column: 7, scope: !154)
!163 = !DILocation(line: 110, column: 14, scope: !154)
!164 = !DILocation(line: 110, column: 7, scope: !154)
!165 = !DILocation(line: 113, column: 21, scope: !6)
!166 = !DILocation(line: 113, column: 55, scope: !6)
!167 = !DILocation(line: 113, column: 3, scope: !6)
!168 = !DILocation(line: 114, column: 3, scope: !6)
!169 = !DILocation(line: 114, column: 6, scope: !6)
!170 = !DILocation(line: 114, column: 12, scope: !6)
!171 = !DILocation(line: 115, column: 3, scope: !6)
!172 = !DILocation(line: 116, column: 1, scope: !6)
!173 = !DILocalVariable(name: "name", arg: 1, scope: !113, file: !1, line: 86, type: !80)
!174 = !DILocation(line: 86, column: 40, scope: !113)
!175 = !DILocalVariable(name: "i", scope: !113, file: !1, line: 88, type: !9)
!176 = !DILocation(line: 88, column: 7, scope: !113)
!177 = !DILocation(line: 90, column: 10, scope: !178)
!178 = distinct !DILexicalBlock(scope: !113, file: !1, line: 90, column: 3)
!179 = !DILocation(line: 90, column: 8, scope: !178)
!180 = !DILocation(line: 90, column: 21, scope: !181)
!181 = !DILexicalBlockFile(scope: !182, file: !1, discriminator: 1)
!182 = distinct !DILexicalBlock(scope: !178, file: !1, line: 90, column: 3)
!183 = !DILocation(line: 90, column: 15, scope: !181)
!184 = !DILocation(line: 90, column: 24, scope: !181)
!185 = !DILocation(line: 90, column: 29, scope: !181)
!186 = !DILocation(line: 90, column: 3, scope: !181)
!187 = !DILocation(line: 92, column: 17, scope: !188)
!188 = distinct !DILexicalBlock(scope: !189, file: !1, line: 92, column: 9)
!189 = distinct !DILexicalBlock(scope: !182, file: !1, line: 91, column: 3)
!190 = !DILocation(line: 92, column: 29, scope: !188)
!191 = !DILocation(line: 92, column: 23, scope: !188)
!192 = !DILocation(line: 92, column: 32, scope: !188)
!193 = !DILocation(line: 92, column: 9, scope: !188)
!194 = !DILocation(line: 92, column: 38, scope: !188)
!195 = !DILocation(line: 92, column: 9, scope: !189)
!196 = !DILocation(line: 93, column: 14, scope: !188)
!197 = !DILocation(line: 93, column: 7, scope: !188)
!198 = !DILocation(line: 94, column: 3, scope: !189)
!199 = !DILocation(line: 90, column: 39, scope: !200)
!200 = !DILexicalBlockFile(scope: !182, file: !1, discriminator: 2)
!201 = !DILocation(line: 90, column: 3, scope: !200)
!202 = !DILocation(line: 95, column: 3, scope: !113)
!203 = !DILocation(line: 97, column: 1, scope: !113)
!204 = !DILocalVariable(name: "a", arg: 1, scope: !110, file: !1, line: 119, type: !10)
!205 = !DILocation(line: 119, column: 60, scope: !110)
!206 = !DILocalVariable(name: "filename", arg: 2, scope: !110, file: !1, line: 119, type: !80)
!207 = !DILocation(line: 119, column: 75, scope: !110)
!208 = !DILocalVariable(name: "def_ext", arg: 3, scope: !110, file: !1, line: 119, type: !80)
!209 = !DILocation(line: 119, column: 98, scope: !110)
!210 = !DILocalVariable(name: "names_index", scope: !110, file: !1, line: 121, type: !9)
!211 = !DILocation(line: 121, column: 7, scope: !110)
!212 = !DILocation(line: 121, column: 37, scope: !110)
!213 = !DILocation(line: 121, column: 21, scope: !110)
!214 = !DILocation(line: 123, column: 7, scope: !215)
!215 = distinct !DILexicalBlock(scope: !110, file: !1, line: 123, column: 7)
!216 = !DILocation(line: 123, column: 19, scope: !215)
!217 = !DILocation(line: 123, column: 7, scope: !110)
!218 = !DILocation(line: 124, column: 35, scope: !215)
!219 = !DILocation(line: 124, column: 19, scope: !215)
!220 = !DILocation(line: 124, column: 17, scope: !215)
!221 = !DILocation(line: 124, column: 5, scope: !215)
!222 = !DILocation(line: 126, column: 7, scope: !223)
!223 = distinct !DILexicalBlock(scope: !110, file: !1, line: 126, column: 7)
!224 = !DILocation(line: 126, column: 19, scope: !223)
!225 = !DILocation(line: 126, column: 7, scope: !110)
!226 = !DILocalVariable(name: "format_state", scope: !227, file: !1, line: 128, type: !9)
!227 = distinct !DILexicalBlock(scope: !223, file: !1, line: 127, column: 3)
!228 = !DILocation(line: 128, column: 9, scope: !227)
!229 = !DILocation(line: 128, column: 31, scope: !227)
!230 = !DILocation(line: 128, column: 25, scope: !227)
!231 = !DILocation(line: 128, column: 44, scope: !227)
!232 = !DILocation(line: 128, column: 52, scope: !227)
!233 = !DILocation(line: 128, column: 24, scope: !227)
!234 = !DILocation(line: 129, column: 9, scope: !235)
!235 = distinct !DILexicalBlock(scope: !227, file: !1, line: 129, column: 9)
!236 = !DILocation(line: 129, column: 22, scope: !235)
!237 = !DILocation(line: 129, column: 9, scope: !227)
!238 = !DILocation(line: 130, column: 22, scope: !235)
!239 = !DILocation(line: 130, column: 16, scope: !235)
!240 = !DILocation(line: 130, column: 35, scope: !235)
!241 = !DILocation(line: 130, column: 43, scope: !235)
!242 = !DILocation(line: 130, column: 15, scope: !235)
!243 = !DILocation(line: 130, column: 7, scope: !235)
!244 = !DILocation(line: 132, column: 14, scope: !235)
!245 = !DILocation(line: 132, column: 7, scope: !235)
!246 = !DILocation(line: 135, column: 21, scope: !110)
!247 = !DILocation(line: 135, column: 55, scope: !110)
!248 = !DILocation(line: 135, column: 3, scope: !110)
!249 = !DILocation(line: 136, column: 3, scope: !110)
!250 = !DILocation(line: 136, column: 6, scope: !110)
!251 = !DILocation(line: 136, column: 12, scope: !110)
!252 = !DILocation(line: 137, column: 3, scope: !110)
!253 = !DILocation(line: 138, column: 1, scope: !110)
!254 = !DILocalVariable(name: "str", arg: 1, scope: !116, file: !1, line: 69, type: !80)
!255 = !DILocation(line: 69, column: 25, scope: !116)
!256 = !DILocalVariable(name: "suffix", arg: 2, scope: !116, file: !1, line: 69, type: !80)
!257 = !DILocation(line: 69, column: 42, scope: !116)
!258 = !DILocalVariable(name: "length_str", scope: !116, file: !1, line: 71, type: !45)
!259 = !DILocation(line: 71, column: 10, scope: !116)
!260 = !DILocalVariable(name: "length_suffix", scope: !116, file: !1, line: 71, type: !45)
!261 = !DILocation(line: 71, column: 22, scope: !116)
!262 = !DILocation(line: 73, column: 8, scope: !263)
!263 = distinct !DILexicalBlock(scope: !116, file: !1, line: 73, column: 7)
!264 = !DILocation(line: 73, column: 12, scope: !263)
!265 = !DILocation(line: 73, column: 21, scope: !263)
!266 = !DILocation(line: 73, column: 25, scope: !267)
!267 = !DILexicalBlockFile(scope: !263, file: !1, discriminator: 1)
!268 = !DILocation(line: 73, column: 32, scope: !267)
!269 = !DILocation(line: 73, column: 7, scope: !267)
!270 = !DILocation(line: 74, column: 5, scope: !263)
!271 = !DILocation(line: 76, column: 23, scope: !116)
!272 = !DILocation(line: 76, column: 16, scope: !116)
!273 = !DILocation(line: 76, column: 14, scope: !116)
!274 = !DILocation(line: 77, column: 26, scope: !116)
!275 = !DILocation(line: 77, column: 19, scope: !116)
!276 = !DILocation(line: 77, column: 17, scope: !116)
!277 = !DILocation(line: 79, column: 7, scope: !278)
!278 = distinct !DILexicalBlock(scope: !116, file: !1, line: 79, column: 7)
!279 = !DILocation(line: 79, column: 21, scope: !278)
!280 = !DILocation(line: 79, column: 18, scope: !278)
!281 = !DILocation(line: 79, column: 7, scope: !116)
!282 = !DILocation(line: 80, column: 19, scope: !283)
!283 = distinct !DILexicalBlock(scope: !278, file: !1, line: 79, column: 36)
!284 = !DILocation(line: 80, column: 26, scope: !283)
!285 = !DILocation(line: 80, column: 39, scope: !283)
!286 = !DILocation(line: 80, column: 37, scope: !283)
!287 = !DILocation(line: 80, column: 23, scope: !283)
!288 = !DILocation(line: 80, column: 55, scope: !283)
!289 = !DILocation(line: 80, column: 12, scope: !283)
!290 = !DILocation(line: 80, column: 5, scope: !283)
!291 = !DILocation(line: 82, column: 5, scope: !292)
!292 = distinct !DILexicalBlock(scope: !278, file: !1, line: 81, column: 10)
!293 = !DILocation(line: 84, column: 1, scope: !116)
